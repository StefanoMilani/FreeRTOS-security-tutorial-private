#include "common_utils.h"

void print_bytes(const uint8_t *bytes, int len)
{
    for (int i = 0; i < len; i++)
    {
        if (i != 0 && i != len - 1 && i % BYTES_PER_LINE == 0)
        {
            printf("\n");
        }

        printf("0x%02X\t", *(bytes + i));
    }
    printf("\n");
}

int generate_random_bytes(uint8_t *out, int len)
{
    RNG rng;

    if (wc_InitRng(&rng) != 0)
    {
        printf("RNG init failed");
        return -1;
    }

    if (wc_RNG_GenerateBlock(&rng, out, len) != 0)
    {
        printf("RNG generate failed");
        return -1;
    }

    return 0;
}