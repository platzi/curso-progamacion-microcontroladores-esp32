#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "nvs_flash.h"
#include "nvs.h"

void app_main(void)
{
  printf("Start!\n");

  // Inicializar el NVS
  esp_err_t err = nvs_flash_init();
  printf("NVS Init!\n");
  printf((err != ESP_OK) ? "Failed\n" : "Done\n");

  // Acceder a una partición de NVS
  nvs_handle_t my_storage;
  err = nvs_open("storage", NVS_READWRITE, &my_storage);
  printf("NVS Open\n");
  printf((err != ESP_OK) ? "Failed\n" : "Done\n");

  // Escribir en NVS
  err = nvs_set_i32(my_storage, "number", 10);
  printf("NVS Set\n");
  printf((err != ESP_OK) ? "Failed\n" : "Done\n");

  // Guardar en NVS
  err = nvs_commit(my_storage);
  printf("NVS Commit\n");
  printf((err != ESP_OK) ? "Failed\n" : "Done\n");

  // Leer NVS
  int32_t number;
  err = nvs_get_i32(my_storage, "number", &number);
  printf("NVS Get\n");
  printf((err != ESP_OK) ? "Failed\n" : "Done\n");

  printf("El valor recuperado es: %d\n", number);
  nvs_close(my_storage);

  printf("End\n");
}
