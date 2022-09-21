#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{

    FILE *FL;

    char *buffer = malloc(100 * sizeof(char) + 1);
    char ret = '\0';
    FL = fopen("testreadfile.txt", "r");

    do
    {
        ret = fscanf(FL, "%s", buffer);
        printf("%s\n", buffer);

    } while (ret != EOF);

    free(buffer);
    return 0;
}