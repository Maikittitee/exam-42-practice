#include <unistd.h>
#include <stdio.h>

unsigned char	reverse_bits(unsigned char octet)
{
    int i;
    unsigned char temp;

    int st[8] = {7,5,3,1,1,3,5,7};
    
    i = 7;
    temp = 0;
    while (i >= 0)
    {
        if (i >= 4)
            temp += (octet & (1 << i)) >> st[i];
        else
            temp += (octet & (1 << i)) << st[i];
        i--;
    }
    return(temp);
}



int main()
{
    printf("%d\n" , reverse_bits(1));
}