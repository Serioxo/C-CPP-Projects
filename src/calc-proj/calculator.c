#include <stdio.h>
#include <stdlib.h>


void calc()
{
    //VARIABLES
    int ModeSelect;
    int inputA;
    int inputB;
    static int modearray[3];

    printf("Select mode:  '\n' 1 '\n' 2'\n' 3'");
    scanf(ModeSelect);

    //MODE SELECTION
    if (modearray[3] == 3){
        int result = inputA + inputB;
        return result;
    }
        if (modearray[3] == 2){
        int result = inputA - inputB;
        return result;
    }
        if (modearray[3] == 1){
        int result = inputA * inputB;
        return result;
    }
}





int main(){
    calc();

    return 0;
}

