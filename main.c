/* Standard includes. */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <sys/select.h>
#include <time.h>

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"

/* Tutotial includes.*/
#include "hashing_tutorial.h"
#include "aes_tutorial.h"
#include "ecc_tutorial.h"

void main(void)
{

    printf("IoT Course 2024: FreeRTOS Security Tutorial\n");

#if ENABLE_HASHING_TUTORIAL
    xTaskCreateStatic(hashingTask,
                      "hashing-tutorial",
                      configMINIMAL_STACK_SIZE,
                      NULL,
                      configMAX_PRIORITIES - 1,
                      &(hashingTaskStack[0]),
                      &(hashingTaskTCB));
#endif // ENABLE_HASHING_TUTORIAL

#if ENABLE_AES_TUTORIAL
    xTaskCreateStatic(aesTask,
                      "aes-tutorial",
                      configMINIMAL_STACK_SIZE,
                      NULL,
                      configMAX_PRIORITIES - 1,
                      &(aesTaskStack[0]),
                      &(aesTaskTCB));
#endif // ENABLE_AES_TUTORIAL

#if ENABLE_ECC_TUTORIAL
    xTaskCreateStatic(eccTask,
                      "ecc-tutorial",
                      configMINIMAL_STACK_SIZE,
                      NULL,
                      configMAX_PRIORITIES - 1,
                      &(eccTaskStack[0]),
                      &(eccTaskTCB));
#endif // ENABLE_ECC_TUTORIAL

#if !ENABLE_HASHING_TUTORIAL && !ENABLE_AES_TUTORIAL && !ENABLE_ECC_TUTORIAL
    printf("Enable at least one tutorial to run.\n");
    printf("To enable a test to run set one the respective define to 1 in the header file.\n");
    printf("For example: #define ENABLE_HASHING_TUTORIAL = 1 in the hashing_tutorial.h file.\n");
    return;
#else
    /* Start the scheduler. */
    vTaskStartScheduler();
#endif
    for (;;)
    {
        /* Should not reach here. */
    }
}
