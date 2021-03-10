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

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

SemaphoreHandle_t bouton_semph; //variable pour le semaphore

task_params_t task_A = {
    .delay = 1000,
    .message = "Task A running\n\r" 
};

task_params_t task_B = {
    .delay = 1000,
    .message = "Task B running\n\r" 
};


//Partie 1 
void vLedBlinkTask(void){
    
    for(;;){
        
        vTaskDelay(pdMS_TO_TICKS(500));
        Cy_GPIO_Write(LED_PORT,LED_NUM,1);
        vTaskDelay(pdMS_TO_TICKS(500));
        Cy_GPIO_Write(LED_PORT,LED_NUM,0);
        
    }
}

//Partie 2 : Interupt pour donner le sémaphore 
void isr_bouton(void)
{
    xSemaphoreGiveFromISR(bouton_semph,NULL);
    Cy_GPIO_ClearInterrupt(Bouton_PORT,Bouton_NUM);
    NVIC_ClearPendingIRQ(Bouton_ISR_cfg.intrSrc);
   
}

//Partie 2 : Fonction qui attend le sémaphore
void bouton_task(void)
{
  for(;;)
  {
    
    xSemaphoreTake(bouton_semph,portMAX_DELAY);
    
    vTaskDelay(pdMS_TO_TICKS(20)); //Debouncing
    
    //UART_PutString("Hello ! \n\n\r");
    
    
    if (Cy_GPIO_Read(Bouton_PORT,Bouton_NUM) == 0)
    {
        UART_PutString("Bouton was pressed! \n\n\r");
    }
    else 
    {
        UART_PutString("Bouton was released! \n\n\r");   
    }
   
  }
}

//Partie 3 : print_loop

void print_loop(void * params)
{
    
    task_params_t parametre = *(task_params_t *)params;
    
    for(;;)
    {
        vTaskDelay(pdMS_TO_TICKS(parametre.delay)); //Période du message
        UART_PutString(parametre.message);   //Message  
    }
   
}


int main(void)
{
    bouton_semph = xSemaphoreCreateBinary(); //2.6 : Initialisation du sémaphore

    __enable_irq(); /* Enable global interrupts. */
    
 
    UART_Start(); //Start UART
    
    /* Initialisation de l'interuption liée au bouton sw2 */
    Cy_SysInt_Init(&Bouton_ISR_cfg, isr_bouton);
    NVIC_ClearPendingIRQ(Bouton_ISR_cfg.intrSrc);
    NVIC_EnableIRQ(Bouton_ISR_cfg.intrSrc);
    
    
    //Créer la tâche de clignotement
    xTaskCreate(vLedBlinkTask,"LedBlink",80,NULL,1,NULL);
    
    //Créer la tâche liée au bouton
    xTaskCreate(bouton_task,"Bouton_task",80,NULL,1,NULL);
    
    //Créer les deux taches de la partie 3
    
    xTaskCreate(print_loop,"Task A",configMINIMAL_STACK_SIZE, (void *) &task_A,1,NULL);
    xTaskCreate(print_loop,"Task B",configMINIMAL_STACK_SIZE, (void *) &task_B,1,NULL);
    
    //Démarrer le Scheduler
    vTaskStartScheduler();

    
    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
