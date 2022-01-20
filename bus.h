/*  Bus Transfers
*   This functions are pratically the same and you can pass both registers as parameters, but in real hardware doenst work like that
*   reg: register you want send data
*   bus: system bus
*/
void loadToBus(int* reg, int* bus){
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
void loadFromBus(int* reg, int* bus){
    for(int i  = 0; i<8; i++)
    {
        reg[i] = bus[i];
    }
}
//  Just to clear the Bus after some data transfer, just in case
void clearBus(int* bus){
    for(int i = 0; i<8; i++)
    {
        bus[i] = 0b0;
    }
}