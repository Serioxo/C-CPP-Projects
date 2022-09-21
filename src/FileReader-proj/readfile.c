#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char ** argv){

    FILE* file;

    char * buffer = malloc(100 * sizeof(char));
    char ret = '\0';
    file = fopen("testreadfile.txt", "r+");

    do
    {
        ret = fscanf(file, "%s",buffer);
        printf("%s\n", buffer);

    } while (ret != EOF);
    
    return 0;
}