#include <unistd.h>

void    print_bits(unsigned char octet)
{
    int i;

    char bit;

    i = 7;
    while (i >= 0)
    {
        bit = (octet >> i) & 0b00000001;

        bit += 48;
        write(1, &bit,1);
        i--;
    }
}

int main()
{
    print_bits(3);
}
