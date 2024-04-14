#include "ecc_tutorial.h"

void eccTask(void *parameter)
{
    printf("ECC Tutorial Task Started.\n");

    /*
        Init the struct(s) needed.
        NOTE: init TWO curve structs to generate the shared secret between the two.
    */
    printf("Initializing 2 ECC keys and RNG...");
    curve25519_key key_1;
    wc_curve25519_init(&key_1); // initialize key
    curve25519_key key_2;
    wc_curve25519_init(&key_2); // initialize key
    WC_RNG rng;
    wc_InitRng(&rng); // initialize random number generator
    printf("DONE.\n");

    /*
        Generate the private and public keys for both ECC keys.
    */
    printf("Generating ECC key...");
    if (wc_curve25519_make_key(&rng, CURVE25519_KEYSIZE, &key_1) != 0)
    {
        perror("Failed to create ECC key");
        return;
    }
    if (wc_curve25519_make_key(&rng, CURVE25519_KEYSIZE, &key_2) != 0)
    {
        perror("Failed to create ECC key");
        return;
    }
    printf("DONE.\n");

    /*
        Export the private and public key for both ECC keys.
    */
    printf("Exporting ECC key...");
    // KEYS 1
    word32 private_key_size_1 = CURVE25519_KEYSIZE;
    byte private_key_1[private_key_size_1];
    if (wc_curve25519_export_private_raw(&key_1, private_key_1, &private_key_size_1) != 0)
    {
        perror("Failed to export private key 1");
        return;
    }

    word32 public_key_size_1 = CURVE25519_KEYSIZE * 2;
    byte public_key_1[public_key_size_1];
    if (wc_curve25519_export_public(&key_1, public_key_1, &public_key_size_1) != 0)
    {
        perror("Failed to export public key 1");
        return;
    }
    // KEYS 2
    word32 private_key_size_2 = CURVE25519_KEYSIZE;
    byte private_key_2[private_key_size_2];
    if (wc_curve25519_export_private_raw(&key_2, private_key_2, &private_key_size_2) != 0)
    {
        perror("Failed to export private key 2");
        return;
    }
    word32 public_key_size_2 = CURVE25519_KEYSIZE * 2;
    byte public_key_2[public_key_size_2];
    if (wc_curve25519_export_public(&key_2, public_key_2, &public_key_size_2) != 0)
    {
        perror("Failed to export public key 2");
        return;
    }
    printf("DONE.\n");

    /*
        Print the private and public key for both ECC keys.
    */
    // PRINT KEYS 1
    printf("Private key 1:\n");
    print_bytes(private_key_1, CURVE25519_KEYSIZE);
    printf("\n");
    printf("Public key 1:\n");
    print_bytes(public_key_1, CURVE25519_KEYSIZE * 2);
    printf("\n");

    // PRINT KEYS 2
    printf("Private key 2:\n");
    print_bytes(private_key_2, CURVE25519_KEYSIZE);
    printf("\n");
    printf("Public key 2:\n");
    print_bytes(public_key_2, CURVE25519_KEYSIZE * 2);
    printf("\n");

    /*
        Generate the first secret using the private of the first key and the public of the second key.
    */
    printf("Generating ECC secrets...");
    word32 secret_size_1 = CURVE25519_KEYSIZE;
    byte secret_1[secret_size_1];
    if (wc_curve25519_shared_secret(&key_1, &key_2, secret_1, &secret_size_1) != 0)
    {
        perror("Failed to generate ECC secret 1");
        return;
    }

    /*
        Generate the second secret using the private of the second key and the public of the first key.
    */
    word32 secret_size_2 = CURVE25519_KEYSIZE;
    byte secret_2[secret_size_2];
    if (wc_curve25519_shared_secret(&key_2, &key_1, secret_2, &secret_size_2) != 0)
    {
        perror("Failed to generate ECC secret 2");
        return;
    }
    printf("DONE.\n");

    /*
        PRINT SECRETS
    */
    printf("Secret 1:\n");
    print_bytes(secret_1, CURVE25519_KEYSIZE);
    printf("\n");
    printf("Secret 2:\n");
    print_bytes(secret_2, CURVE25519_KEYSIZE);
    printf("\n");

    /*
        Compare the two secrets.
    */
    if (memcmp(secret_1, secret_2, CURVE25519_KEYSIZE) != 0)
    {
        printf("The computed secrets are different.\n");
        return;
    }
    printf("The computed secrets are equals.\n");

    printf("\n");
    printf("ECC Tutorial Task Completed.\n");

    // Leave it to flush stdout
    fflush(stdout);
    for (;;)
    {
    }
}