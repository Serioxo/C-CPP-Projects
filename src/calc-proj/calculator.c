#include <stdio.h>
#include <stdlib.h>



int add(int a,int b){
    return a + b;
}

int sub(int a, int b){
    return a - b;
}

int multi(int a, int b){
    return a * b;
}

void calc()
{
    //VARIABLES
    int ModeSelect;
    int inputA;
    int inputB;
    int checker;
    int result;

    printf("Select mode:  '\n' 1: Addition'\n' 2: Subtractions'\n' 3: Multiplication' '\n'");
    scanf("%d", &checker);
    scanf("%d", &inputA);
    scanf("%d", &inputB);

    switch (checker)
    {
    case 1:
        result = add(inputA,inputB);
        break;

    case 2:
        result = sub(inputA,inputB);
        break;

    case 3:
        result = multi(inputA,inputB);
        break;

    default:
        printf("Error: Wrong input given try again");
        break;
    }

    printf("the result is: %d", result);

}


int main(){
    calc();

    return 0;
}

