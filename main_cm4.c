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


void vLedBlinkTask(void){
    
    for(;;){
        
        vTaskDelay(pdMS_TO_TICKS(500));
        //vTaskDelay(500);
        Cy_GPIO_Write(LED_PORT,LED_NUM,1);
        vTaskDelay(pdMS_TO_TICKS(500));
        //vTaskDelay(500);
        Cy_GPIO_Write(LED_PORT,LED_NUM,0);
        
    }
}

int main(void)
{

    __enable_irq(); /* Enable global interrupts. */
    
    
    xTaskCreate(vLedBlinkTask,"LedBlink",80,NULL,1,NULL);
    vTaskStartScheduler();
    
    

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    
    
    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
