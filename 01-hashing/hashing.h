#ifndef HASHING_H
#define HASHING_H

// Set to 1 to enable hashing
#define ENABLE_HASHING 1

// Set to 1 to enable hashing debug output 1

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

#endif