#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

TaskHandle_t taskHandle1 = NULL;
TaskHandle_t taskHandle2 = NULL;

void task1(void *args) {
  int count = 0;
  while(1) {
    count++;
    printf("Task 1 count: %d\n", count);
    if (count == 3) {
      vTaskSuspend(taskHandle2);
      printf("Task 2 suspend\n");
    }
    if (count == 10) {
      vTaskResume(taskHandle2);
      printf("Task 2 resume\n");
    }
    if (count == 12) {
      vTaskDelete(taskHandle2);
      printf("Task 2 deleted\n");
    }
    if (count == 15) {
      printf("Task 1 deleted\n");
      vTaskDelete(NULL);
    }
  }
}

void task2(void *args) {
  int count = 0;
  while(1) {
    count++;
    printf("Task 2 count: %d\n", count);
    if (count == 15) {
      vTaskDelete(NULL);
    }
  }
}

void app_main(void)
{
  xTaskCreate(task1, "task1", 4096, NULL, 10, &taskHandle1);
  xTaskCreatePinnedToCore(task2, "task2", 4096, NULL, 10, &taskHandle2, 1);
}
