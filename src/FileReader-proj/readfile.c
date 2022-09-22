
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
   char ch, file_name[150];
   FILE *file;

   printf("Enter name of a file you wish to see\n");
   gets(file_name);

   file = fopen(file_name, "r"); // read mode

   printf("The contents of %s file are:\n", file_name);

   while((ch = fgetc(file)) != EOF)
      printf("%c", ch);

   fclose(file);
   return 0;
}