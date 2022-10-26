#include <stdio.h>
#include "esp_wifi.h"
#include "nvs_flash.h"
#include "protocol_examples_common.h"

void app_main(void)
{
  nvs_flash_init();
  esp_netif_init();
  esp_event_loop_create_default();

  example_connect();

  esp_netif_ip_info_t ip_info;
  esp_netif_t* netif = NULL;
  netif = esp_netif_get_handle_from_ifkey("WIFI_STA_DEF");

  if (netif == NULL) {
    printf("No hay interfaz\n");
  } else {
    esp_netif_get_ip_info(netif, &ip_info);
    printf("IP: %d.%d.%d.%d\n", IP2STR(&ip_info.ip));
  }
}
