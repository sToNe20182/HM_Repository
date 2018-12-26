/*************************************************************************
    > File Name: fusion_alg_manager.c
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
#include "main_screen.h"


TimerHandle_t xTimerofSDM;
QueueHandle_t raw_data_queue_handle;
static TaskHandle_t fusion_alg_manager_task_handle;

static void raw_data_process_msg_handler(fusion_alg_msg_struct_t *message)
{
    if(!message)
    {
        return;
    }
    switch(message->message_id)
    {
        case MESSAGE_ID_RAW_SENSOR_DATA:
            //inject_raw_sensor_data((raw_sensor_data*) message->param2);
            GRAPHICLOG("===========wells==========MESSAGE_ID_RAW_SENSOR_DATA");
            break;
		case MESSAGE_ID_RAW_GPS_DATA:
			//inject_raw_gps_data((raw_sensor_data*) message->param2);
			 GRAPHICLOG("===========wells==========MESSAGE_ID_RAW_GPS_DATA");
			break;
        default :
            break;
    }
}
// 发送消息到 fusion alg task
int32_t fusion_alg_send_event(fusion_alg_msg_status_id event_id, int32_t param1, void* param2)
{
    fusion_alg_msg_struct_t message;
	TickType_t ticks;
    message.message_id = event_id;
    message.param1 = param1;
    message.param2 = param2;
	ticks = 1000 / portTICK_PERIOD_MS;
    return xQueueSend(raw_data_queue_handle, &message, ticks);
}

void fusion_alg_mgr_task(void * arg)
{
    fusion_alg_msg_struct_t fusion_alg_event_data_item;

    while(1)
    {
        if (xQueueReceive(raw_data_queue_handle, &fusion_alg_event_data_item, portMAX_DELAY))
        {
            raw_data_process_msg_handler(&fusion_alg_event_data_item);
        }
    }
}

int32_t fusion_alg_manager_init(void)
{
    raw_data_queue_handle = xQueueCreate(FUSION_MGR_QUEUE_SIZE,sizeof(fusion_alg_msg_struct_t));
    xTaskCreate(fusion_alg_mgr_task, FUSION_ALG_MANAGER_TASK_NAME, FUSION_ALG_MANAGER_TASK_STACKSIZE / sizeof(StackType_t), NULL, FUSION_ALG_MANAGER_TASK_PRIO,&fusion_alg_manager_task_handle);
    return 1;
}
