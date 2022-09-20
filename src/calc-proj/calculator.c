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

    //MODE SELECTION
    if (checker == 3){
        result = inputA + inputB;
        printf("The Result is: " + result);
        
    }
        if (checker == 2){
        int result = inputA - inputB;
        printf("The Result is: " + result);
    }
        if (checker == 1){
        int result = inputA * inputB;
        printf("The Result is: " + result);       
    }

    else if (checker != 1,2,3)
    {
        __THROW(printf("Error: Wrong input given try again"));
    }
}

int main(){
    calc();

    return 0;
}

