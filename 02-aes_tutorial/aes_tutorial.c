#include "aes_tutorial.h"

void aesTask(void *parameters)
{

    printf("AES Tutorial Task Started.\n");

    Aes cbc_enc;
    Aes cbc_dec;
    void *hint = NULL;
    int devId = INVALID_DEVID; // if not using async INVALID_DEVID is default
    byte plaintext[] = "Hello, World! And some other stuff to have a plaintext longer than the AES128 blocksize";
    word32 plaintext_len = strlen(plaintext);
    printf("Plaintext: %s\tLen: %u\n", plaintext, plaintext_len);
    int n = (plaintext_len / AES_BLOCK_SIZE) + 1;

    // GENERATE KEY
    printf("Generating Key... ");
    byte key[AES_128_KEY_SIZE] = {0x00};
    if (generate_random_bytes((uint8_t *)key, AES_128_KEY_SIZE) != 0)
    {
        perror("Failed to generate key");
        return;
    }
    printf("DONE.\n");
    printf("Key:\n");
    print_bytes(key, AES_128_KEY_SIZE);

    // GENERATE IV
    printf("Generating IV... ");
    byte iv[AES_IV_SIZE] = {0x00};
    if (generate_random_bytes((uint8_t *)iv, AES_IV_SIZE) != 0)
    {
        perror("Failed to generate IV");
        return;
    }
    printf("DONE.\n");

    /*
     *  CBC ENCRYPTION MODE
     */
    printf("\nCBC ENCRYPTION MODE\n\n");

    // INIT AES CONTEXT
    printf("Initializing AES context... ");
    if (wc_AesInit(&cbc_enc, hint, devId) != 0)
    {
        perror("Failed to initialize AES context");
        return;
    }
    printf("DONE.\n");

    // SET KEY AND IV
    printf("Setting Key and IV... ");
    if (wc_AesSetKey(&cbc_enc, key, AES_128_KEY_SIZE, iv, AES_ENCRYPTION) != 0)
    {
        perror("Failed to set key and IV");
        return;
    }
    printf("DONE.\n");

    // ENCRYPT DATA
    printf("Encrypting Data using CBC... ");
    word32 ciphertext_len = n * AES_BLOCK_SIZE;
    byte ciphertext[ciphertext_len]; // multiple of 16 bytes
    memset(ciphertext, 0, ciphertext_len);
    byte plaintext_padded[ciphertext_len];
    memset(plaintext_padded, 0, ciphertext_len);
    memcpy(plaintext_padded, plaintext, plaintext_len);
    if (wc_AesCbcEncrypt(&cbc_enc, ciphertext, plaintext_padded, ciphertext_len) != 0)
    {
        perror("Failed to encrypt data");
        return;
    }
    printf("DONE.\n");
    printf("Ciphertext:\n");
    print_bytes(ciphertext, ciphertext_len);

    // Free AES context
    wc_AesFree(&cbc_enc);

    /*
     *  CBC DECRYPTION MODE
     */
    printf("\nCBC DECRYPTION MODE\n\n");

    // INIT AES CONTEXT
    printf("Initializing AES context... ");
    if (wc_AesInit(&cbc_dec, hint, devId) != 0)
    {
        perror("Failed to initialize AES context");
        return;
    }
    printf("DONE.\n");

    // SET KEY AND IV
    printf("Setting Key and IV... ");
    if (wc_AesSetKey(&cbc_dec, key, AES_128_KEY_SIZE, iv, AES_DECRYPTION) != 0)
    {
        perror("Failed to set key and IV");
        return;
    }
    printf("DONE.\n");

    // DECRYPT DATA
    printf("Decrypting Data using CBC... ");
    byte plaintext_decrypted_padded[ciphertext_len];
    if (wc_AesCbcDecrypt(&cbc_dec, plaintext_decrypted_padded, (const byte *)ciphertext, ciphertext_len) != 0)
    {
        perror("Failed to decrypt data");
        return;
    }
    printf("DONE.\n");
    printf("Plaintext Decrypted Padded:\n");
    print_bytes(plaintext_decrypted_padded, ciphertext_len);
    word32 plaintext_decrypted_len = strlen(plaintext_decrypted_padded);
    byte plaintext_decrypted[plaintext_decrypted_len];
    memcpy(plaintext_decrypted, plaintext_decrypted_padded, plaintext_len);
    printf("Plaintext Decrypted:\n");
    print_bytes(plaintext_decrypted, plaintext_len);
    printf("Original Plaintext:\n");
    print_bytes(plaintext, plaintext_len);

    if (memcmp(plaintext_decrypted, plaintext, plaintext_len) != 0)
    {
        printf("Decrypted data does not match plaintext\n");
    }
    else
    {
        printf("Decrypted data matches plaintext\n");
    }

    // Free AES context
    wc_AesFree(&cbc_dec);

    // Leave it to flush stdout
    fflush(stdout);
    for (;;)
    {
    }
}