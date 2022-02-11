int convertToDecimal(int *vector){
    int temp = 0, decimal = 0, base = 1, remainder;
    for(int i = 0; i<8; i++)
    {
        temp += vector[i];
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
    return decimal;
}

int* convertToBinary(int numberToConvert){
    int result[8]={0b0};

    for(int i=7; numberToConvert>0;i--)
    {
        result[i] =numberToConvert%2;
        numberToConvert = numberToConvert/2;
    }
    return &result;
}