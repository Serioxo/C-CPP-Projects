#include <stdio.h>
#include <stdlib.h>


void calc()
{
    //VARIABLES
    int ModeSelect;
    int inputA;
    int inputB;
    int checker;
    int result;

    scanf("Select a mode: ");
    printf("Select mode:  '\n' 1: Addition'\n' 2: Subtractions'\n' 3: Multiplication' '\n'");


    scanf("%d %d", &inputA, &inputB);



    switch (checker)
    {
    case 1:
        result = inputA + inputB;
        printf("The Result is: " + result);
        break;
    

    case 2:
        int result = inputA - inputB;
        printf("The Result is: " + result);
        break;

    case 3:
        int result = inputA * inputB;
        printf("The Result is: " + result); 
        break;

    default:
        __THROW(printf("Error: Wrong input given try again"));
        break;
    }

}

int main(){
    calc();

    return 0;
}

