#include "common_utils.h"

void print_bytes(const char *bytes, int len)
{
    for (int i = 0; i < len; i++)
    {
        if (i != 0 && i != len - 1 && i % 6 == 0)
        {
            printf("\n");
        }
        printf("0x%X\t", bytes[i]);
    }
    printf("\n");
}