#include <stdio.h>
#include "esp_chip_info.h"

void app_main()
{
  esp_chip_info_t chip_info;
  esp_chip_info(&chip_info);
  printf("Este es un chip tipo %s, y tiene %d cores!\n",
    CONFIG_IDF_TARGET,
    chip_info.cores
  );
}
