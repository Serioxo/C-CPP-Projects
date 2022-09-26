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
    bool isActive;

} customer;
  int tl,sl,ts;

void writefile(){
    FILE *fp;
    fp = fopen("/Client-Data/client.dat", "ab");
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
        FILE *fp=fopen("/Client-Data/client.dat","rb");
	  fseek (fp,0,SEEK_END);
	  tl=ftell(fp);
	  sl=sizeof(customer);
	  ts=tl/sl;
	  fseek(fp,(ts-1)*sl,SEEK_SET);
	  fread(&customer,sizeof(customer),1,fp);
	  printf("\ncustomer ID:%d\n",++customer.id);
	  fclose(fp);
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


   void output()
	 {
	   printf("\n\n    Customer no    :%d\n",customer.id);
	   printf("    Name 	   :%s\n",customer.name);
	   printf("    Mobile no      :%.f\n",customer.mobilenum);
	   printf("    Account number :%d\n",customer.address_street);
	   printf("    City           :%s\n",customer.city);
	   printf("    Payment date   :%d/%d/%d\n\n",customer.birthday.month,customer.birthday.day,customer.birthday.year);
	   printf("    Account Status :%s\n",customer.isActive);
     }



int main()
{
    int i,n;
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
    return 0;
    do{
	       printf("\nselect what do you want to do?");
	       ch=getche();
	  }while(ch<='0' || ch>'3');
	  switch(ch){
		case '1':
			clrscr();
			printf("\nhow many customer accounts?");
			scanf("%d",&n);
			for(i=0;i<n;i++){
				input();
				writefile();
			}
			main();
		case '2':
			clrscr();
			printf("search by what?\n");
			printf("\n1 --- search by customer number\n");
			printf("2 --- search by customer name\n");
			search();
			ch=getche();
			main();
		case '3':
			clrscr();
			delay(700);
			gotoxy(25,25);
			cprintf("\nA PROJECT BY BIDUR & SUJAN");
			delay(1500);
			exit(1);
	  }
}

