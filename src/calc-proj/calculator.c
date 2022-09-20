#include <stdio.h>
#include <stdlib.h>


void calc()
{
    //VARIABLES
    int ModeSelect;
    int inputA;
    int inputB;
    static int modearray[4];

    printf("Select mode:  '\n' 1 '\n' 2'\n' 3'\n' 4");
    scanf(ModeSelect);

    //MODE SELECTION
    if (modearray[4] == 4){
        int result = inputA + inputB;
        return result;
    }
}





int main(){
    calc();

    return 0;
}

