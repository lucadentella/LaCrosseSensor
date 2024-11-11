#ifndef _GLOBALS_H
#define _GLOBALS_H

// SPI LoRa Radio for Xiao 
#define LORA_SCK  8
#define LORA_MISO 9
#define LORA_MOSI 10
#define LORA_CS   7
#define LORA_RST  6

// Sensor constants
#define SENSOR_ID           1
#define UPDATE_PERIOD       10  // in seconds
#define NEW_BATTERY_CYCLES  10  // in UPDATE_PERIOD times
#define FRAME_LENGTH        5   // do not change!

// Uncomment this line to enable serial debugging
//#define DEBUG 

// Debug functions
#ifdef DEBUG
#define DPRINT(...)    Serial.print(__VA_ARGS__)
#define DPRINTLN(...)  Serial.println(__VA_ARGS__)
#define DRINTF(...)    Serial.print(F(__VA_ARGS__))
#define DPRINTLNF(...) Serial.println(F(__VA_ARGS__))
#define DBEGIN(...)    Serial.begin(__VA_ARGS__)
#else
#define DPRINT(...)     //blank line
#define DPRINTLN(...)   //blank line
#define DPRINTF(...)    //blank line
#define DPRINTLNF(...)  //blank line
#define DBEGIN(...)     //blank line
#endif

#endif