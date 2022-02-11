
#define TRUE  1
#define FALSE 0

/*             
*                Arithmetic Logic Unit

*        reg1, reg2: registers that will be use in the operations
*        bus: where the output will be transfered
*        sum, sub: which operation will be performed, sum or subtraction
*/
void alu(int* reg1, int* reg2, int* bus, int sum, int sub) {

    int result[8] = {0b0}; //Suport array for operations
    int carry = 0b0; //This is to simulate the carry bit in some eletronics
    
    if(sum == TRUE && sub == FALSE){// If we are adding the registers
        
        for(int i = 7; i>0; i--){

            switch (carry){
            case 0:
                if(reg1[i] == 1 && reg2[i] == 1){
                    result[i] = 0b0;
                    carry = 0b1;
                }
                if(reg1[i] == 1 && reg2[i] == 0){
                    result[i] = 0b1;
                    carry = 0b0;
                }
                if(reg1[i] == 0 && reg2[i] == 1){
                    result[i] = 0b1;
                    carry = 0b0;
                }
                if(reg1[i] == 0 && reg2[i] == 0){
                    result[i] = 0b0;
                    carry = 0b0;
                }
                break;
            case 1:
                if(reg1[i] == 1 && reg2[i] == 1){
                    result[i] = 0b1;
                    carry = 0b1;
                }
                if(reg1[i] == 1 && reg2[i] == 0){
                    result[i] = 0b0;
                    carry = 0b1;
                }
                if(reg1[i] == 0 && reg2[i] == 1){
                    result[i] = 0b0;
                    carry = 0b1;
                }
                if(reg1[i] == 0 && reg2[i] == 0){
                    result[i] = 0b1;
                    carry = 0b0;   
                }
                break;
            }
        }
        loadToBus(result, bus);//Sending the result
    }

    /*
     Subtracting two binary numbers is just a different way to adding them
     Throught the 'two complements' we can invert the number, turning them into a neagative number, add 1 and the result will be right
     UNLESS you subtract a bigger number than the first one, might rework that later
     TODO: Negative Numbers https://github.com/andrelu00/8BitComputer/issues/3
    */
    else if(sum == FALSE && sub == TRUE){// If we are subtracting the registers
        int complement = 0b1;
        int tempArray[8]; 
        for(int i =0; i<8; i++){// Inverting the number
            if(reg2[i] == 0b0){
                tempArray[i] = 0b1;
            }
            else if(reg2[i] == 0b1){
                tempArray[i] = 0b0;
            }
        }
        for(int i = 7; i>0; i--){

            if(i == 7){
                result[i] += 1;
            }

            switch (carry){
            case 0:
                if(reg1[i] == 1 && tempArray[i] == 1){
                    result[i] = 0b0;
                    carry = 0b1;
                }
                if(reg1[i] == 1 && tempArray[i] == 0){
                    result[i] = 0b1;
                    carry = 0b0;
                }
                if(reg1[i] == 0 && tempArray[i] == 1){
                    result[i] = 0b1;
                    carry = 0b0;
                }
                if(reg1[i] == 0 && tempArray[i] == 0){
                    result[i] = 0b0;
                    carry = 0b0;
                }
                break;
            case 1:
                if(reg1[i] == 1 && tempArray[i] == 1){
                    result[i] = 0b1;
                    carry = 0b1;
                }
                if(reg1[i] == 1 && tempArray[i] == 0){
                    result[i] = 0b0;
                    carry = 0b1;
                }
                if(reg1[i] == 0 && tempArray[i] == 1){
                    result[i] = 0b0;
                    carry = 0b1;
                }
                if(reg1[i] == 0 && tempArray[i] == 0){
                    result[i] = 0b1;
                    carry = 0b0;   
                }
                break;
            } 
        }
        loadToBus(result, bus);//Sending the result
    }
}