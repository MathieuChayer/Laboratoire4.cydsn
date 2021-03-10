/* ========================================
********************************************

Laboratoire 4

Mathieu Chayer    (1950287)
Parsa Maghsoudloo (1963539)

********************************************
* ========================================*/
#include "project.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "params.h"
#include "queue.h"

int x = 10; 
int main(void)
{
    __enable_irq(); /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
