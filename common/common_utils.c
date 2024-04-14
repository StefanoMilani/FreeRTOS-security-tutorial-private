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

/*
    @brief Generates a random block of bytes of length len.
    @param out: the buffer to store the random bytes.
    @param len: the length of the random bytes to generate.
    @return 0 on success, -1 on failure.
*/
int generate_random_bytes(uint8_t *out, int len)
{

    /*
        INIT THE STRUCT(S) needed for the RNG.
    */

    RNG rng;
    if (wc_InitRng(&rng) != 0)
    {
        printf("RNG init failed");
        return -1;
    }

    /*
        GENERATE A BLOCK OF RANDOM BYTES OF LENGTH len.
    */
    if (wc_RNG_GenerateBlock(&rng, out, len) != 0)
    {
        printf("RNG generate failed");
        return -1;
    }

    return 0;
}