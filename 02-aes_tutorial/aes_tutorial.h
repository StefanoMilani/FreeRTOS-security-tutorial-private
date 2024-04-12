#ifndef AES_TUTORIAL_H
#define AES_TUTORIAL_H

// Set to 1 to enable aes tutorial
#define ENABLE_AES_TUTORIAL 0

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

/* COMMON UTILITIES INCLUDES */
#include "common_utils.h"

/* WOLFSSL includes. */
#include "wolfssl/wolfcrypt/aes.h"

static StaticTask_t aesTaskTCB;
static StackType_t aesTaskStack[configMINIMAL_STACK_SIZE];

void aesTask(void *parameters);

#endif /* AES_TUTORIAL_H */
