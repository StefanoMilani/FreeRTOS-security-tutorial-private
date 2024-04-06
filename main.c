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

    /* Start the scheduler. */
    vTaskStartScheduler();

    for (;;)
    {
        /* Should not reach here. */
    }
}
