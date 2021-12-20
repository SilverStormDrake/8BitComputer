/*  
*   8 Bit PC emulator inspired by Ben Eater "Bulding an 8-bit breadboard Computer!" youtube series
*   Made by: André Luiz(andrelu00) 
*/

#include <stdio.h>
#include <stdlib.h>

#define TRUE  1
#define FALSE 0

/*  
*   This function seems useles, but its just to emulate a real clock.
*   In other complex systems it might be convenient to track the clock cycle. 
*/
void clockCycle(int* ptr)//Clock
{
    (*ptr)++;
}

/*  Bus Transfers
*   This functions are pratically the same and you can pass both registers as parameters, but in real hardware doenst work like that
*   reg: register you want send data
*   bus: system bus
*/
void loadToBus(int* reg, int* bus)
{
    for(int i  = 0; i<8; i++)
    {
        bus[i] = reg[i];
    }
}
/*  Bus Transfers
*
*   This functions are pratically the same and you can pass both registers as parameters, but in real hardware doens't work like that
*   reg: register you want to load data 
*   bus: system bus
*/
void loadFromBus(int* reg, int* bus)
{
    for(int i  = 0; i<8; i++)
    {
        reg[i] = bus[i];
    }
}
//  Just to clear the Bus after some data transfer
void clearBus(int* bus)
{
    for(int i = 0; i<8; i++)
    {
        bus[i] = 0b0;
    }
}

/*             Arithmetic Logic Unit
* 
*  reg1, reg2: registers that will be use in the operations
*  bus: where the output will be transfered
*  sum, sub: which operation will be performed, sum or subtraction
*/
void alu(int* reg1, int* reg2, int* bus, int sum, int sub) 
{
    int result[8] = {0b0}; //Suport array for operations
    int carry = 0b0; //This is to simulate the carry bit in some eletronics
    
    if(sum == TRUE && sub == FALSE)// If we are adding the registers
    {
        for(int i = 7; i<0; i--)
        {
            result[i] = reg1[i]+ reg2[1] + carry;

            if(result[i] > 0b1 && i == 7)
            {
                result[i] = 0b0;
                carry = 0b1;
            }
            else
            {
                switch (carry)
                {
                case 0:
                    if(reg1[i] == 1 && reg2[i] == 1)
                    {
                        result[i] = 0b0;
                        carry = 0b1;
                    }
                    if(reg1[i] == 1 && reg2[i] == 0)
                    {
                        result[i] = 0b1;
                        carry = 0b0;
                    }
                    if(reg1[i] == 0 && reg2[i] == 1)
                    {
                        result[i] = 0b1;
                        carry = 0b0;
                    }
                    if(reg1[i] == 0 && reg2[i] == 0)
                    {
                        result[i] = 0b0;
                        carry = 0b0;
                    }
                    break;
                case 1:
                    if(reg1[i] == 1 && reg2[i] == 1)
                    {
                        result[i] = 0b1;
                        carry = 0b1;
                    }
                    if(reg1[i] == 1 && reg2[i] == 0)
                    {
                        result[i] = 0b0;
                        carry = 0b1;
                    }
                    if(reg1[i] == 0 && reg2[i] == 1)
                    {
                        result[i] = 0b0;
                        carry = 0b1;
                    }
                    if(reg1[i] == 0 && reg2[i] == 0)
                    {
                        result[i] = 0b1;
                        carry = 0b0;   
                    }
                    break;
                }
            }
        }
        //Debuging
        printf("Result:");
        for(int i =0; i<8;i++)
        {
            printf(" %i",result[i]);
        }
    }
    else if(sum == FALSE && sub == TRUE)// If we are subtracting the registers
    {

    }
}

int main()
{
    int on = TRUE;
    int turnOff;

    int* clock = 0;

    /*
    *   In the video theres a huge discussion about the registers and the bus
    *   But i will just use some arrays for the emulator
    */
    int registerA[8]           = {0b0 , 0b1 , 0b1, 0b0, 0b1, 0b0, 0b0, 0b0};
    int registerB[8]           = {0b0};
    int bus[8]                 = {0b0};
    int instructionRegister[8] = {0b0}; //This is a special register that will be used later

    while(on==1)//Computer Loop
    {
        //Commands
        clockCycle(&clock);
        loadToBus(&registerA, &bus);
        loadFromBus(&registerB, &bus);
        clearBus(&bus);
        alu(&registerA, &registerB, &bus, TRUE, FALSE);

        //Visualization of the computer
        printf("\nClock Cycle: %i\n", clock);
        printf("\nRegister A\n");
        for(int i = 0; i <8; i++)
        {
            printf("%i ",registerA[i]);

            if(i == 7)
            {
                printf("\n");
            }
        }
        printf("\nRegister B\n");
        for(int i = 0; i <8; i++)
        {
            printf("%i ",registerB[i]);

            if(i == 7)
            {
                printf("\n");
            }
        }
        printf("\nBus\n");
        for(int i = 0; i <8; i++)
        {
            printf("%i ",bus[i]);

            if(i == 7)
            {
                printf("\n");
            }
        }


        /*
        * Just to finish the program through terminal
        * This is a janky solution, might rework later
        */
        scanf(" %i", &turnOff);
        if(turnOff == FALSE)
        {
            on = FALSE;
        }
        
    }

    return 0;
}