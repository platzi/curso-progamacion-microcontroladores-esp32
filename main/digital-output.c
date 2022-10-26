#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED_PIN 4
#define BLINK_TIME 1000

void app_main(void)
{
  int led_state = 0;
  gpio_reset_pin(LED_PIN);
  gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

  while (1)
  {
    gpio_set_level(LED_PIN, led_state);
    led_state = !led_state;
    vTaskDelay(BLINK_TIME / portTICK_PERIOD_MS);
  }
}
