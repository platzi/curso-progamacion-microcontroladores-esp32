#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "driver/ledc.h"

#define LEDC_TIMER LEDC_TIMER_0// Timer que usarémos
#define LEDC_MODE LEDC_HIGH_SPEED_MODE // Modo de velocidad
#define LEDC_OUTPUT 12 // Pin de salida
#define LEDC_CHANNEL LEDC_CHANNEL_0 // Canal de control
#define LEDC_DUTY_RES LEDC_TIMER_12_BIT // Resolución en bits
#define LEDC_FREQUENCY 5000 // Frecuencia de funcionamiento
#define LEDC_DUTY 0 // Valor inicial
#define LEDC_HPOINT 0 // Ajuste de fase

void app_main() {
  ledc_timer_config_t ledc_timer = {
    .speed_mode = LEDC_MODE,
    .timer_num = LEDC_TIMER,
    .duty_resolution = LEDC_DUTY_RES,
    .freq_hz = LEDC_FREQUENCY,
    .clk_cfg = LEDC_AUTO_CLK
  };
  ledc_timer_config(&ledc_timer);

  ledc_channel_config_t ledc_channel = {
    .speed_mode = LEDC_MODE,
    .channel = LEDC_CHANNEL,
    .timer_sel = LEDC_CHANNEL,
    .intr_type = LEDC_INTR_DISABLE,
    .gpio_num = LEDC_OUTPUT,
    .duty = LEDC_DUTY,
    .hpoint = LEDC_HPOINT
  };
  ledc_channel_config(&ledc_channel);

  adc2_config_channel_atten(ADC2_CHANNEL_6, ADC_ATTEN_DB_0);
  int32_t raw_value;

  while(1) {
    adc2_get_raw(ADC2_CHANNEL_6, ADC_WIDTH_BIT_12, &raw_value);
    printf("adc raw: %d\n", raw_value);

    ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, raw_value);
    ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);

    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
