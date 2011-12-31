#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
        char c = 128;
        unsigned char uc = 256;
        signed char sc = 128;
        const char cc = 128;
        wchar_t wc = 2147483648;

        printf("Implied Char:  %d\n", c);
        printf("Unsigned Char: %d\n", uc);
        printf("Signed Char:   %d\n", sc);
        printf("Const Char:    %d\n", cc);
        printf("Wide Char:     %d\n", wc);
        return 0;
}
