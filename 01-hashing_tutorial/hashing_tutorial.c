#include "hashing_tutorial.h"

void hashingTask(void *parameters)
{
    /* Unused parameters. */
    (void)parameters;

    printf("Hashing Tutorial Task Started.\n");

    byte data[] = "Hello, World!";
    word32 len = strlen(data);
    printf("Hashing...\tData: %s\tLen: %u\n", data, len);
    byte hash[WC_SHA256_DIGEST_SIZE] = {0x00};

    /*
        Initialize the needed structs(s) needed for the SHA256.
    */
    Sha256 sha256;

    printf("Initializing hash context... ");
    if (wc_InitSha256(&sha256) != 0)
    {
        perror("\nwc_InitSha256 failed");
        return;
    }
    printf("DONE\n");

    /*
        Update the hashing context with the data.
    */

    printf("Updating hashing context... ");
    /* UPDATE HASH CONTEXT */
    if (wc_Sha256Update(&sha256, data, len) != 0)
    {
        perror("\nwc_Sha256Update failed");
        return;
    }
    printf("DONE\n");

    /*
        Finalize hash.
    */
    printf("Finalizing hash... ");
    if (wc_Sha256Final(&sha256, hash) != 0)
    {
        perror("\nwc_Sha256Final failed");
        return;
    }
    printf("DONE\n");

    /*
        Free the hash context.
    */
    printf("Freeing Hash Context.. ");
    wc_Sha256Free(&sha256);
    printf("DONE\n");

    /*
        Print the hash.
    */
    printf("Hash:\n");
    print_bytes((const uint8_t *)&hash, WC_SHA256_DIGEST_SIZE);
    printf("\n");

    printf("Hashing task finished.\n");

    // Leave it to flush stdout
    fflush(stdout);
    for (;;)
    {
    }
}
