#include "hashing.h"

void hashingTask(void *parameters)
{
    /* Unused parameters. */
    (void)parameters;

    printf("Hashing task started.\n");

    Sha256 sha256;
    int ret;
    byte data[] = "Hello, World!";
    word32 len = sizeof(data);
    printf("Data: %s\n", data);
    byte hash[WC_SHA256_DIGEST_SIZE] = {0x00};

    printf("Initializing hash context... ");
    ret = wc_InitSha256(&sha256);
    if (ret != 0)
    {
        perror("\nwc_InitSha256 failed");
        return;
    }
    printf("DONE\n");

    printf("Updating hashing context... ");
    /* UPDATE HASH CONTEXT */
    ret = wc_Sha256Update(&sha256, data, len);
    if (ret != 0)
    {
        perror("\nwc_Sha256Update failed");
        return;
    }
    printf("DONE\n");

    /* FINALIZE HASH */
    printf("Finalizing hash... ");
    ret = wc_Sha256Final(&sha256, hash);
    if (ret != 0)
    {
        perror("\nwc_Sha256Final failed");
        return;
    }
    printf("DONE\n");

    printf("Freeing Hash Context.. ");
    wc_Sha256Free(&sha256);
    printf("DONE\n");

    /* Print the hash. */
    printf("Hash:\n");
    // print_bytes((const char *)hash, WC_SHA256_DIGEST_SIZE);
    for (int i = 0; i < WC_SHA256_DIGEST_SIZE; i++)
    {
        printf("%hhu", hash[i]);
    }
    printf("\n");
    printf("Hashing task finished.\n");
    // Leave it to allow console print
    for (;;)
    {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
