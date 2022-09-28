#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define Birthday of customer
struct birthdate
{
	int month;
	int day;
	int year;
};

// Define Customer Profile
struct customer
{
	int id;
	char name[200];
	int mobilenum;
	char address_street[100];
	char city[100];
	struct birthdate birthday;

} customer;

int tellreturn, fsize, tellsize;

void writefile()
{

	FILE *fp = NULL;
	fp = fopen("/workspaces/C-CPP-Projects/src/information-sys-proj/Client-Data/client.dat", "ab");
	fwrite(&customer, sizeof(customer), 1, fp);
	fclose(fp);
	return;
}
// Adds client to system
void addClient()
{
}
// Removes client from system
void removeClient()
{
}
// Edit client info
void editClient()
{
}

// Get data about client
int getData()
{
	// DIRECTORY MUST BE CHANGED DEPENDING ON WHERE "CLIENT.DAT" FILE IS STORED
	FILE *fp = fopen("/workspaces/C-CPP-Projects/src/information-sys-proj/Client-Data/client.dat", "r");
	fseek(fp, 0, SEEK_CUR);
	tellreturn = ftell(fp);
	fsize = sizeof(customer);
	tellsize = tellreturn / fsize;
	char currentID = customer.id;
	fseek(fp, (tellsize - 1) * fsize, SEEK_SET);
	fread(&customer, sizeof(customer), 1, fp);
	printf("Last Customer ID: %d\n", customer.id);
	fclose(fp);
	printf("\nNew Customer ID: ");
	scanf("%s/%c", currentID);
	printf("\n       Name:");
	scanf("%s", customer.name);
	printf("\n       mobile no:");
	scanf("%i", &customer.mobilenum);
	printf("         Street:");
	scanf("%s", customer.address_street);
	printf("         City:");
	scanf("%s", customer.city);
	printf("         Brithday (mm/dd/yyyy):");
	scanf("%d/%d/%d", &customer.birthday.month, &customer.birthday.day, &customer.birthday.year);
	return 0;
}
// Call viewClient via ID
void checkClientID(int ID)
{
	output();
}

void output()
{
	printf("\n\nCustomer ID    :%d\n", customer.id);
	printf("    Name 	       :%s\n", customer.name);
	printf("    Mobile no      :%.d\n", customer.mobilenum);
	printf("    Address 	   :%s\n", customer.address_street);
	printf("    City           :%s\n", customer.city);
	printf("    Birth date     :%d/%d/%d\n\n", customer.birthday.month, customer.birthday.day, customer.birthday.year);
}

int main()
{
	int i, n;
	char ch;
	printf("\t\t\t***********************************\n");
	printf("\t\t\t** WELCOME TO INFORMATION HANDLER **\n");
	printf("\t\t\t***********************************\n");
	printf("\t\t\t             BY JAKUB MIGAC \n");
	printf("\t\t\t***********************************\n");
	printf("\t\t\t\t\tMENU\n\n\n");
	printf("\t\t\t\t1-ADD CLIENT\n");
	printf("\t\t\t\t2-REMOVE CLIENT\n");
	printf("\t\t\t\t3-EDIT CLIENT\n");
	printf("\t\t\t\t4-SEARCH CLIENT VIA ID\n");
	printf("\t\t\t\tESC- TO EXIT.\n\n\n");
	printf("\t\t\t***********************************\n\n\n");

	do
	{
		printf("\nselect what do you want to do? ");
		ch = getchar();
	} while (ch <= '0' || ch > '3');
	switch (ch)
	{
	case '1':
		system("clear");
		printf("\nhow many customer accounts would you like to add? ");
		scanf("%d", &n);
		for (i = 0; i < n; i++)
		{
			getData();
			writefile();
		}
		main();
	case '2':
		system("clear");
		printf("search by what?\n");
		printf("\n1 --- Output Customer information via ID\n");
		output();
		ch = getchar();
		main();
	case '3':
		system("clear");
		printf("Please Type customer ID: ");
		int id = scanf("%s");
		checkClientID(id);
		main();
	case '4':
		system("clear");
		printf("\n\n\n\n\nProject by jakub migac");
		exit(1);
	}
}
