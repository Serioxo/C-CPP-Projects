#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <sstream>
#include <chrono>
#include <thread>
#include <vector>
#include <numeric>

using json = nlohmann::json;
using namespace std;

// Replace with your KuCoin API keys
const string API_KEY = "your_api_key";
const string API_SECRET = "your_api_secret";
const string API_PASSPHRASE = "your_api_passphrase";
const string BASE_URL = "https://api.kucoin.com";
const string SYMBOL = "BTC-USDT";  // Example trading pair

// Bot settings
const int MAX_REQUESTS = 100;  // Limit of 100 requests per second (public)
const int INTERVAL_MS = 100;   // Delay between requests in milliseconds
const double SPREAD = 0.05;    // Spread for micro price changes
const int SMA_PERIOD = 20;     // Period for Simple Moving Average (SMA)

// Function to get historical prices (candlesticks)
vector<double> getHistoricalPrices() {
    string url = BASE_URL + "/api/v1/market/candles?symbol=" + SYMBOL + "&type=1hour&size=" + to_string(SMA_PERIOD);
    CURL* curl = curl_easy_init();
    string response;

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            cerr << "CURL error: " << curl_easy_strerror(res) << endl;
            return {};
        }
        curl_easy_cleanup(curl);
    }

    // Parse JSON response and extract closing prices
    auto data = json::parse(response);
    vector<double> prices;
    for (const auto& candle : data["data"]) {
        prices.push_back(stod(candle[2].get<string>()));  // Close price is at index 2
    }
    return prices;
}

// Function to calculate the Simple Moving Average (SMA)
double calculateSMA(const vector<double>& prices) {
    if (prices.size() < SMA_PERIOD) {
        cerr << "Not enough data for SMA calculation" << endl;
        return 0.0;
    }
    double sum = accumulate(prices.begin(), prices.end(), 0.0);
    return sum / prices.size();
}

// Function to get current market price
double getMarketPrice() {
    string url = BASE_URL + "/api/v1/market/orderbook/level1?symbol=" + SYMBOL;
    CURL* curl = curl_easy_init();
    string response;

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            cerr << "CURL error: " << curl_easy_strerror(res) << endl;
            return 0.0;
        }
        curl_easy_cleanup(curl);
    }

    // Parse JSON response
    auto data = json::parse(response);
    return stod(data["data"]["price"].get<string>());
}

// Write callback for curl responses
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

// Function to place order (buy/sell)
void placeOrder(const string& side, double price, double quantity) {
    string url = BASE_URL + "/api/v1/orders";
    CURL* curl = curl_easy_init();
    if (curl) {
        string orderData = "{\"side\":\"" + side + "\",\"symbol\":\"" + SYMBOL + "\",\"price\":\"" +
                           to_string(price) + "\",\"size\":\"" + to_string(quantity) + "\",\"type\":\"limit\",\"stp\":\"CO\"}";
        // Setup headers and authentication for private API access
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, ("KC-API-KEY: " + API_KEY).c_str());
        headers = curl_slist_append(headers, ("KC-API-SIGN: " + API_SECRET).c_str());
        headers = curl_slist_append(headers, ("KC-API-TIMESTAMP: " + to_string(chrono::system_clock::now().time_since_epoch().count())).c_str());
        headers = curl_slist_append(headers, ("KC-API-PASSPHRASE: " + API_PASSPHRASE).c_str());

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, orderData.c_str());
        CURLcode res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            cerr << "Order placement failed: " << curl_easy_strerror(res) << endl;
        }

        curl_easy_cleanup(curl);
    }
}

// Function to simulate rate limit handler
void handleRateLimit(int requestCount) {
    if (requestCount >= MAX_REQUESTS) {
        cout << "Rate limit exceeded. Sleeping for 1 second..." << endl;
        this_thread::sleep_for(chrono::seconds(1));  // Sleep to avoid hitting the limit
    }
}

// Function to determine the market trend based on SMA
string getMarketTrend(double currentPrice, double sma) {
    if (currentPrice > sma) {
        return "uptrend";   // Price above SMA indicates an uptrend
    } else if (currentPrice < sma) {
        return "downtrend"; // Price below SMA indicates a downtrend
    } else {
        return "neutral";   // Price equal to SMA
    }
}

int main() {
    try {
        int requestCount = 0;

        while (true) {
            // Get historical prices for trend analysis
            vector<double> prices = getHistoricalPrices();
            if (prices.empty()) {
                cout << "Error fetching historical prices. Retrying..." << endl;
                this_thread::sleep_for(chrono::milliseconds(INTERVAL_MS));
                continue;
            }

            // Calculate the SMA and determine the trend
            double sma = calculateSMA(prices);
            double currentPrice = getMarketPrice();

            // Handle rate limit
            requestCount++;
            handleRateLimit(requestCount);

            // Determine market trend
            string trend = getMarketTrend(currentPrice, sma);
            cout << "Current Trend: " << trend << endl;

            // Adjust trading strategy based on trend
            if (trend == "uptrend") {
                // Place buy order with spread during uptrend
                double buyPrice = currentPrice * (1 - SPREAD / 100);
                double sellPrice = currentPrice * (1 + SPREAD / 100);
                double orderQuantity = 0.1;
                placeOrder("buy", buyPrice, orderQuantity);
                placeOrder("sell", sellPrice, orderQuantity);
            } else if (trend == "downtrend") {
                // Place sell order during downtrend
                double sellPrice = currentPrice * (1 + SPREAD / 100);
                double orderQuantity = 0.1;
                placeOrder("sell", sellPrice, orderQuantity);
            }

            this_thread::sleep_for(chrono::milliseconds(INTERVAL_MS));  // Wait between requests
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}