#include "utils.h"
//Memory Functions
void writeMemory(int *ram, int *bus, int address)
{
    ram[address] = convertToDecimal(*bus);
}

void readMemory(int *ram, int *bus, int address)
{
    int result[8] = convertToBinary(ram[address]);

    loadToBus(result, bus);
}
