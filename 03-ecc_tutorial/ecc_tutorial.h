#ifndef ECC_TUTORIAL_H
#define ECC_TUTORIAL_H

// Set to 1 to enable aes tutorial
#define ENABLE_ECC_TUTORIAL 0

/* FreeRTOS kernel includes. */
#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>

/* COMMON UTILITIES INCLUDES */
#include <common_utils.h>
#include <config.h>

/* WOLFSSL includes. */
#include <wolfssl/wolfcrypt/random.h>
#include <wolfssl/wolfcrypt/curve25519.h>

static StaticTask_t eccTaskTCB;
static StackType_t eccTaskStack[configMINIMAL_STACK_SIZE];

void eccTask(void *parameters);

#endif /* ECC_TUTORIAL_H */
