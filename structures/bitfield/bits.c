#include <stdio.h>
enum _bits {
        unsigned int a : 1;
        unsigned int b : 1;
        unsigned int c : 1;
        unsigned int d : 1;
}

enum *bits = &_bits;
