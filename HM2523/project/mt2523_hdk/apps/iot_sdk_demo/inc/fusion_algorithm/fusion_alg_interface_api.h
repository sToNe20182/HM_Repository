/*************************************************************************
    > File Name: fusion_alg_interface_api.c
    > Author: wells
    > Mail: wangweicsd@126.com
    > Created Time:2018-12-26 13:21
 ************************************************************************/

#ifndef __FUSION_ALG_INTERFACE_API_H__
#define __FUSION_ALG_INTERFACE_API_H__

#include <stdint.h>
#include <string.h>
#include "bsp_lcd.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"

#define MAX_SENSOR_DATA_SIZE   (3)
#define MAX_ALGO_MODE_SIZE     (7)

typedef	struct tag_GPGGA_DATA 
{ 
	uint8_t 	Hour;							//
	uint8_t 	Minute;							//
	uint8_t 	Second;							//
	uint16_t 	MSecond;					    //
	double 	  Latitude;						// < 0 = South, > 0 = North
	double 	  BLatitude;						// < 0 = South, > 0 = North
	uint8_t   SNth;
	double 	  Longitude;						// < 0 = West, > 0 = East
	double 	  BLongitude;						// < 0 = West, > 0 = East
	uint8_t   WEst;
	uint8_t 	GPSQuality;						// 0 = fix not available, 1 = GPS sps mode, 2 = Differential GPS, SPS mode, fix valid, 3 = GPS PPS mode, fix valid
	uint8_t 	NumOfSatsInUse;					//
	double 	  HDOP;							//
	double 	  Altitude;						// Altitude: mean-sea-level (geoid) meters
	uint8_t   Auint;
	double    Geoidal;                        // Geoid Separation
	uint8_t   Guint;
	double    DTime;                          // ²î·ÖÊ±¼ä
	uint16_t  DGpsID;                         // ²î·ÖID
	uint8_t   IDValid;
	uint32_t 	Count;							   //
	int32_t 	OldVSpeedSeconds;				//
	double 	  OldVSpeedAlt;					//
	double 	  VertSpeed;						//
    uint8_t   DFID_Data[4];
	uint8_t   Gp_PN_Kind;
	uint8_t   Utc_Flag;
} GPGGA_DATA;

typedef	struct tag_GPRMC_DATA { 
	uint8_t 	Hour;							//
	uint8_t 	Minute;							//
	uint8_t 	Second;							//
	uint16_t 	MSecond;							//
	uint8_t 	DataValid;						// A = Data valid, V = navigation rx warning
	double 	  Latitude;						// current latitude
	uint8_t   SNth;
	double 	  Longitude;						// current longitude
	uint8_t   WEst;
	double 	  GroundSpeed;					// speed over ground, knots
	double 	  Course;							// course over ground, degrees true
	uint8_t   SpeedValid;
	uint8_t   CourseValid;
	uint8_t 	Day;							//
	uint8_t 	Month;							//
	uint16_t 	Year;							//
	double 	  MagVar;							// magnitic variation, degrees East(+)/West(-)
	uint8_t   MagVarValid;
	uint8_t   MagWEst;                        // ModeIndicator A=Autonomous,D=Differential,E=Dead Reckoning,N=None;
	uint8_t   ModeIn;                         // ModeIndicator A=Autonomous,D=Differential,E=Dead Reckoning,N=None;
	uint32_t 	Count;							//
	uint8_t   Gp_PN_Kind;
	uint8_t   TimeValid;
	uint8_t   DayValid;
} GPRMC_DATA;

typedef	struct tag_GPGST_DATA { 
	float   GstRms;
	float   GstDetaLat;
	float   GstDetaLon;
	float   GstDetaAli;
} GPGST_DATA;


typedef struct
{
   unsigned long   gnss_sys_time;
   GPGGA_DATA      gpgga_data;
   GPRMC_DATA      gprmc_data;
   GPGST_DATA      gpgst_data;
}GNSSData;

typedef struct
{
    unsigned long        sensor_sys_time;                        
    float                axyz[MAX_SENSOR_DATA_SIZE];      
    float                gxyz[MAX_SENSOR_DATA_SIZE];
}RawSensorData;



void inject_sensor_data();  
void inject_location_data(const GNSSData *gnssData);
void init_fusion_alg_data();



#endif
