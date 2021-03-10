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

SemaphoreHandle_t bouton_semph;


//Partie 1 
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

//Partie 2 : Interupt pour donner le sémaphore 
void isr_bouton(void)
{
    xSemaphoreGiveFromISR(bouton_semph,NULL);
    Cy_GPIO_ClearInterrupt(Bouton_0_PORT,Bouton_0_NUM);
    NVIC_ClearPendingIRQ(Bouton_ISR_cfg.intrSrc);

}

//Partie 2 : Fonction qui attend le sémaphore
void bouton_task()
{

}

int main(void)
{
    bouton_semph = xSemaphoreCreateBinary(); //2.6 : Initialisation du sémaphore

    __enable_irq(); /* Enable global interrupts. */
    
    /* Initialisation de l'interuption lié au bouton sw2 */
    Cy_SysInt_Init(&Bouton_ISR_cfg, isr_bouton);
    NVIC_ClearPendingIRQ(Bouton_ISR_cfg.intrSrc);
    NVIC_EnableIRQ(Bouton_ISR_cfg.intrSrc);
    
    xTaskCreate(vLedBlinkTask,"LedBlink",80,NULL,1,NULL);
    vTaskStartScheduler();
    
    

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    
    
    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
