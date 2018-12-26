/*************************************************************************
    > File Name: fusion_alg_interface_api.c
    > Author: wells
    > Mail: wangweicsd@126.com
    > Created Time:2018-12-25 13:21
 ************************************************************************/

#include <string.h>
#include "bsp_lcd.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"
#include "hal_cache.h"
#include "hal_mpu.h"
#include "hal_uart.h"
#include "hal_clock.h"
#include "fusion_alg_manager.h"
#include "task_def.h"
#include "fusion_alg_interface_api.h"
#include "hal_gpt.h"

void inject_sensor_data(const RawSensorData *sensorData) 
{
    fusion_alg_send_event(MESSAGE_ID_RAW_SENSOR_DATA, NULL, sensorData);

}
void inject_location_data(const GNSSData *gnssData)
{
    fusion_alg_send_event(MESSAGE_ID_RAW_GPS_DATA,NULL,NULL);

}

void init_fusion_alg_data()
{
	hal_gpt_init(HAL_GPT_2);
	hal_gpt_register_callback(HAL_GPT_2, inject_location_data, NULL);
	hal_gpt_start_timer_ms(HAL_GPT_2, 50, HAL_GPT_TIMER_TYPE_REPEAT);
}

