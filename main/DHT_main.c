/*

	DHT22 sensor reading test

	Jun 2007: Ricardo Timmermann, implemetation

	MODIFIED: DEC 2022 by Zhivko Y. Krastev

*/

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "rom/ets_sys.h"
#include "nvs_flash.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

#include "DHT22.h"

void DHT_task(void *pvParameter)
{
	setDHTgpio( 32 );
	printf( "Starting DHT Task\n\n");

	while(1) {
	
		printf("=== Reading DHT ===\n" );
		int ret = readDHT();
		
		errorHandler(ret);

		printf( "Hum %.1f\n", getHumidity() );
		printf( "Tmp %.1f\n", getTemperature() );
		
		// -- wait at LEAST 2 sec before reading again ------------
		// The interval of whole process must be beyond 2 seconds !! 
		vTaskDelay( 3000 / portTICK_PERIOD_MS );
	}
}

void app_main()
{
	nvs_flash_init();
    printf("portTICK_PERIOD_MS: %ld\n", portTICK_PERIOD_MS);
	vTaskDelay( 2000 / portTICK_PERIOD_MS );
	xTaskCreate( &DHT_task, "DHT_task", 2048, NULL, 5, NULL );
}

