#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
        int i;
        for(i = 1; i < argc; i += 1)
        {
                printf("%d ", argv[i][0]);
        }
        puts("\n");
        return 0;
}
