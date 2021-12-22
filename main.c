/*  
*   8 Bit PC emulator inspired by Ben Eater "Bulding an 8-bit breadboard Computer!" youtube series
*   Made by: André Luiz(andrelu00) 
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TRUE  1
#define FALSE 0
//This is a way to print binary numbers that i found on StackOverflow by user William Whyte
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0') 

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
    for(int i = 0; i<8; i++)
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
        for(int i = 7; i>0; i--)
        {
            result[i] = reg1[i]+ reg2[i] + carry;

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
        loadToBus(&result, bus);//Sending the result
    }

    /*
    * Subtracting two binary numbers is just a different way to adding them
    * Throught the 'two complements' we can invert the number, turning them into a neagative number, add 1 and the result will be right
    * UNLESS you subtract a bigger number than the first one, might rework that later
    */
    else if(sum == FALSE && sub == TRUE)// If we are subtracting the registers
    {
        int complement = 0b1;
        for(int i =0; i<8; i++)// Inverting the number
        {
            if(reg2[i] == 0b0)
            {
                reg2[i] = 0b1;
            }
            else if(reg2[i] == 0b1)
            {
                reg2[i] = 0b0;
            }
        }
        for(int i = 7; i>0; i--)
        {
            result[i] = reg1[i]+ reg2[i] + carry;

            if(i == 7)
            {
                result[i] += 1;
            }

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

        for(int i =0; i<8; i++)//Inverting the number back to normal
        {
            if(reg2[i] == 0b0)
            {
                reg2[i] = 0b1;
            }
            else if(reg2[i] == 0b1)
            {
                reg2[i] = 0b0;
            }
        }
        loadToBus(&result, bus);//Sending the result
    }
}


//Memory Functions
void writeMemory(int *ram, int *bus, int address)
{
    int temp = 0, decimal = 0, base = 1, remainder;
    for(int i = 0; i<8; i++)
    {
        temp += bus[i];
        if(i !=7)
        {
            temp *= 10;
        }
    }
    while(temp>0)
    {
        remainder = temp%10;
        decimal += (remainder * base);
        temp = temp/10;
        base *= 2;
    }
    ram[address] = decimal;
}

void readMemory(int *ram, int *bus, int address)
{
    int numberToConvert = ram[address];
    int result[8]={0b0};

    for(int i=0; numberToConvert>0;i++)
    {
        result[i] =numberToConvert%2;
        numberToConvert = numberToConvert/2;
    }
    loadToBus(&result, bus);
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
    int registerA[8]           = {0b0 , 0b0, 0b0, 0b0, 0b0, 0b1, 0b1, 0b1};
    int registerB[8]           = {0b0 , 0b0, 0b0, 0b0, 0b0, 0b0, 0b1, 0b1};
    int bus[8]                 = {0b0 , 0b0, 0b0, 0b0, 0b0, 0b0, 0b0, 0b0};
    int instructionRegister[8] = {0b0}; //This is a special register that will be used later
    int ram[16]                = {0b0};

    while(on==1)//Computer Loop
    {
        //Commands
        clockCycle(&clock);
        //alu(&registerA, &registerB, &bus, TRUE, FALSE);
        loadToBus(&registerA, &bus);
        writeMemory(&ram, &bus, 0);
        //readMemory(&ram, &bus, 0);


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
        printf("\nRAM\n");
        for(int i = 0; i<16; i++)
        {
            printf("| %i -", ram[i]);
            printf(" "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(ram[i]));
            printf(" ");
            if(i == 15)
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