#include "bus.h"


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
    //TODO: Sometimes error on this function
    loadToBus(&result, bus);
}
