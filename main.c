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
#include "hashing.h"

void main(void)
{

    printf("IoT Course 2024\nFreeRTOS Security Tutorial\n");

#if ENABLE_HASHING
    xTaskCreateStatic(hashingTask,
                      "hashing-tutorial",
                      configMINIMAL_STACK_SIZE,
                      NULL,
                      configMAX_PRIORITIES - 1,
                      &(hashingTaskStack[0]),
                      &(hashingTaskTCB));
#endif // ENABLE_HASHING

    /* Start the scheduler. */
    vTaskStartScheduler();

    for (;;)
    {
        /* Should not reach here. */
    }
}
