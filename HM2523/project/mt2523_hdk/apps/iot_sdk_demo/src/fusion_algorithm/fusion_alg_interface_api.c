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
#include "main_screen.h"

TimerHandle_t g_read_sensor_timer = NULL;

void inject_sensor_data() 
{
    fusion_alg_send_event(MESSAGE_ID_RAW_SENSOR_DATA, 1,NULL);

}
void inject_location_data(const GNSSData *gnssData)
{
    fusion_alg_send_event(MESSAGE_ID_RAW_GPS_DATA,1,gnssData);

}

void stop_delay_time()
{
    if(g_read_sensor_timer != NULL)
    {
       xTimerStop(g_read_sensor_timer, 0);
       xTimerDelete(g_read_sensor_timer, 0);
    }
    g_read_sensor_timer = NULL;
}

void start_read_sensor_time(uint8_t time,TimerCallbackFunction_t callback)
{
    g_read_sensor_timer = xTimerCreate("delay_timer",
                                    (time/ portTICK_PERIOD_MS),
                                    pdPASS,
                                    0,
                                    callback
                                 );
    xTimerStart(g_read_sensor_timer, 0);
}


void init_fusion_alg_data()
{
    start_read_sensor_time(50,inject_sensor_data);
	//hal_gpt_init(HAL_GPT_2);
	//hal_gpt_register_callback(HAL_GPT_2, inject_sensor_data, NULL);
	//hal_gpt_start_timer_ms(HAL_GPT_2, 100, HAL_GPT_TIMER_TYPE_REPEAT);
}

