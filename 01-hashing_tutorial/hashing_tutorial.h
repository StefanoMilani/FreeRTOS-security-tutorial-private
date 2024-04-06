#ifndef HASHING_TUTORIAL_H
#define HASHING_TUTORIAL_H

// Set to 1 to enable hashing tutorial
#define ENABLE_HASHING_TUTORIAL 0

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

/* COMMON UTILITIES INCLUDES */
#include "common_utils.h"

/* WOLFSSL includes. */
#include "wolfssl/wolfcrypt/sha.h"
#include "wolfssl/wolfcrypt/sha256.h"

static StaticTask_t hashingTaskTCB;
static StackType_t hashingTaskStack[configMINIMAL_STACK_SIZE];

void hashingTask(void *parameters);

#endif /* HASHING_TUTORIAL_H */