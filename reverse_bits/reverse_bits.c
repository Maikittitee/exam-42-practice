#include <unistd.h>
#include <stdio.h>

unsigned char	reverse_bits(unsigned char octet)
{
    int i;
    unsigned char temp;
    unsigned char first;
    unsigned char end;

    int st[8] = {7,5,3,1,1,3,5,7};
    
    i = 7;
    temp = 0;
    // first = octet >> 4;
    // end = octet << 4;
    
    // temp = (first & 0b00010000) << 3;
    // first = first >> 1;
    // first += temp;
    // temp = (end & 0b00000001)  << 3;
    // end = end >> 1;
    // end += temp;

    // return (first >> 4 | end << 4);
    // while (i >= 0)
    // {
    //     if (i >= 4)
    //         temp += (octet & (1 << i)) >> st[i];
    //     else
    //         temp += (octet & (1 << i)) << st[i];
    //     i--;
    // }
    while (i >= 0)
    {
        temp = temp << 1;
        temp = temp + ((octet & 0b10000000) >> 7);
        octet = octet << 1;
        i--;
    }
    return(temp);
}



int main()
{
    printf("%d\n" , reverse_bits(64));
    // printf("37 << 3  = %d\n", 37 << 3);
    // printf("37 << 2  = %d\n", 37 << 2);
    // printf("37 << 1  = %d\n", 37 << 1);
    // printf("37 >> 1  = %d\n", 37 >> 1);
    // printf("37 >> 2  = %d\n", 37 >> 2);
    // printf("37 >> 3  = %d\n", 37 >> 3);
    // printf("37 & 128 = %d\n", 37 & 128 >> 1);
    // printf("37 & 128 = %d\n", 37 & 128 >> 2);
    // printf("37 & 128 = %d\n", 37 & 128 >> 3);
    // printf("37 & 128 = %d\n", 37 & 128 >> 4);
    // printf("37 & 128 = %d\n", 37 & 128 >> 5);
    // printf("37 & 128 = %d\n", 37 & 128 >> 6);
    // printf("37 & 128 = %d\n", 37 & 128 >> 7);
}