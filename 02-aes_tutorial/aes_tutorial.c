#include "aes_tutorial.h"

void aesTask(void *parameters)
{

    printf("AES Tutorial Task Started.\n");

    byte plaintext[] = "Hello, World! And some other stuff to have a plaintext longer than the AES128 blocksize";
    word32 plaintext_len = strlen(plaintext);
    printf("Plaintext: %s\tLen: %u\n", plaintext, plaintext_len);

    /*
        Init the structs needed for encrypting and decrypting
        using the AES algorithm in CBC mode.
        NOTE: different structs are needed for encrypting and decrypting!
    */
    Aes cbc_enc;
    Aes cbc_dec;
    void *hint = NULL;
    int devId = INVALID_DEVID; // if not using async INVALID_DEVID is default
    int n = (plaintext_len / AES_BLOCK_SIZE) + 1;

    /*
        Generate a random key of size AES_128_KEY_SIZE.
        NOTE: this key will be used for encrypting and decrypting.
        NOTE: use the generate_random_bytes implemented in part 0.
    */
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

    /*
        Generate a random IV of size AES_IV_SIZE.
        NOTE: this IV will be used for encrypting and decrypting.
        NOTE: use the generate_random_bytes implemented in part 0.
    */
    printf("Generating IV... ");
    byte iv[AES_IV_SIZE] = {0x00};
    if (generate_random_bytes((uint8_t *)iv, AES_IV_SIZE) != 0)
    {
        perror("Failed to generate IV");
        return;
    }
    printf("DONE.\n");

    /*
        CBC ENCRYPTION MODE
    */
    printf("\nCBC ENCRYPTION MODE\n\n");

    /*
        Init the structs needed for encrypting.
    */
    printf("Initializing AES context... ");
    if (wc_AesInit(&cbc_enc, hint, devId) != 0)
    {
        perror("Failed to initialize AES context");
        return;
    }
    printf("DONE.\n");

    /*
        Update the encryption context with the key and IV.
    */
    printf("Setting Key and IV... ");
    if (wc_AesSetKey(&cbc_enc, key, AES_128_KEY_SIZE, iv, AES_ENCRYPTION) != 0)
    {
        perror("Failed to set key and IV");
        return;
    }
    printf("DONE.\n");

    /*
        Encrypt the plaintext.
        NOTE: the plaintext shall be padded to a multiple of AES_BLOCK_SIZE bytes!
    */
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

    /*
        Print the ciphertext.
    */
    printf("Ciphertext:\n");
    print_bytes(ciphertext, ciphertext_len);

    /*
        Free the encryption AES context.
    */
    wc_AesFree(&cbc_enc);

    /*
     *  CBC DECRYPTION MODE
     */
    printf("\nCBC DECRYPTION MODE\n\n");

    /*
        Init the structs needed for decrypting.
    */
    printf("Initializing AES context... ");
    if (wc_AesInit(&cbc_dec, hint, devId) != 0)
    {
        perror("Failed to initialize AES context");
        return;
    }
    printf("DONE.\n");

    /*
        Update the decryption context with the key and IV.
    */
    printf("Setting Key and IV... ");
    if (wc_AesSetKey(&cbc_dec, key, AES_128_KEY_SIZE, iv, AES_DECRYPTION) != 0)
    {
        perror("Failed to set key and IV");
        return;
    }
    printf("DONE.\n");

    /*
        Decrypt the plaintext.
        NOTE: the result is padded to a multiple of AES_BLOCK_SIZE bytes!
        NOTE: remove padding to obtain the plaintext.
    */
    printf("Decrypting Data using CBC... ");
    byte plaintext_decrypted_padded[ciphertext_len];
    if (wc_AesCbcDecrypt(&cbc_dec, plaintext_decrypted_padded, (const byte *)ciphertext, ciphertext_len) != 0)
    {
        perror("Failed to decrypt data");
        return;
    }
    printf("DONE.\n");

    /*
        Free the decryption AES context.
    */
    wc_AesFree(&cbc_dec);

    /*
        Print the plaintext.
    */
    printf("Plaintext Decrypted Padded:\n");
    print_bytes(plaintext_decrypted_padded, ciphertext_len);
    printf("\n");
    word32 plaintext_decrypted_len = strlen(plaintext_decrypted_padded);
    byte plaintext_decrypted[plaintext_decrypted_len];
    memcpy(plaintext_decrypted, plaintext_decrypted_padded, plaintext_len);
    printf("Plaintext Decrypted:\n");
    print_bytes(plaintext_decrypted, plaintext_len);
    printf("\n");
    printf("Original Plaintext:\n");
    print_bytes(plaintext, plaintext_len);
    printf("\n");

    /*
        Compare the original plaintext with the decrypted plaintext.
    */
    if (memcmp(plaintext_decrypted, plaintext, plaintext_len) != 0)
    {
        printf("Original plaintext and Decrypted data are different.\n");
    }
    else
    {
        printf("Original plaintext and Decrypted data are equals.\n");
    }

    printf("\n");
    printf("AES Tutorial Task Completed.\n");

    // Leave it to flush stdout
    fflush(stdout);
    for (;;)
    {
    }
}