#include <stdio.h>
#include <pico/stdlib.h>
#include <pico/sync.h>
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#define IN_PIN 7
#define OUT_PIN 8

int toggle = 1;
QueueHandle_t msg_queue;
void irq_callback(uint gpio, uint32_t event_mask)
{
    // for(int i = 0; i<100000; i++){
    //     __nop();

    // }
    xQueueSendFromISR(msg_queue,&event_mask,NULL);

}



void toggle_task(__unused void *params){
    for(;;){
    int toggle_value;
xQueueReceiveFromISR(msg_queue,&toggle_value,NULL);
    if (toggle_value & GPIO_IRQ_EDGE_RISE) {
        gpio_put(OUT_PIN, true);
    } else if (toggle_value & GPIO_IRQ_EDGE_FALL) {
        gpio_put(OUT_PIN, false);
    }
    }
}


int main(void)
{
    stdio_init_all();

    gpio_init(IN_PIN);
    gpio_set_dir(IN_PIN, GPIO_IN);

    gpio_init(OUT_PIN);
    gpio_set_dir(OUT_PIN, GPIO_OUT);
    gpio_put(OUT_PIN, toggle);

    gpio_set_irq_enabled_with_callback(IN_PIN, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL , true, irq_callback);

    msg_queue = xQueueCreate(10,sizeof(int));
    const char *rtos_name = "FreeRTOS";
    TaskHandle_t task;
    xTaskCreate(toggle_task, "MainThread",
                configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 2UL, &task);
    vTaskStartScheduler();


    while(1) __wfi();
    return 0;
}
