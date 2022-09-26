#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

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
  int tl,sl,ts;
void kill()
{
    exi(_Exit);
}

// Adds client to system
void addClient()
{
    FILE *fp;
    fp = fopen("/Client-Data/client.dat", "ab");
    fwrite(&customer, sizeof(customer), 1, fp);
    fclose(fp);
    return;
}
// Removes client from system
void removeClient()
{
}
// Edit client info
void editClient()
{
}
// View client info
void viewClient()
{
}
// Get data about client
int getData()
{
        FILE *fp=fopen("/Client-Data/client.dat","rb");
	  fseek (fp,0,SEEK_END);
	  tl=ftell(fp);
	  sl=sizeof(customer);
	  ts=tl/sl;
	  fseek(fp,(ts-1)*sl,SEEK_SET);
	  fread(&customer,sizeof(customer),1,fp);
	  printf("\ncustomer ID:%d\n",++customer.id);
	  fclose(fp);
	  printf("         Account number:");
	  scanf("%d",&customer.name);
	  printf("\n       Name:");
	  scanf("%s",customer.name);
	  printf("\n       mobile no:");
	  scanf("%f",&customer.mobilenum);
	  printf("         Street:");
	  scanf("%s",customer.address_street);
	  printf("         City:");
	  scanf("%s",customer.city);
	  printf("         Brithday (mm/dd/yyyy):");
	  scanf("%d/%d/%d",&customer.birthday.month,&customer.birthday.day,&customer.birthday.year);
	  return;
}
// Call viewClient via ID
void checkClientID(int ID)
{
}

int main()
{
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
    return 0;
}
