/*  8 Bit PC emulator inspired by Ben Eater "Bulding an 8-bit breadboard Computer!"
*   Made by: André Luiz(andrelu00)
*   Im redoing this project
*   
*/

#include <stdio.h>

void processor(int* ptr)
{
    (*ptr)++;
}

int main()
{
    int on = 1;
    int* clock = 0;
    int turnOff;


    while(on==1)//Computer Loop
    {
        processor(&clock);
        printf("%i\n", clock); 
        
        
        scanf("%i", &turnOff);//Just to finish the program through terminal
        if(turnOff == 0)
        {
            on = 0;
        }
    }

    return 0;
}