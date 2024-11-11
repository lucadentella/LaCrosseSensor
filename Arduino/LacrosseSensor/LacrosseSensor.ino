#include <SPI.h>
#include <Wire.h>
#include <ArduinoLowPower.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include "SX127x.h"
#include "lacrosse.h"
#include "globals.h"

Adafruit_BME280 bme;
SX127x SX(LORA_CS, LORA_RST);

const int frequency = 868300;
const int dataRate = 17241;

float temperature = 20.0;
int humidity = 50;
long cycles = 0;

void sendPacket() {

  // do a forced measurement
  bool result = bme.takeForcedMeasurement();
  if(result) {
    temperature = bme.readTemperature();
    humidity = (int)bme.readHumidity(); // Lacrosse only support integer values for Humidity
  } else {
    DPRINTLN("Forced measurement failed, using previous values");
  }

  DPRINT("Sending ");
  DPRINT(temperature);
  DPRINT("°C, ");
  DPRINT(humidity);
  DPRINT("%... ");

  bool newBattery = false;
  if(++cycles < NEW_BATTERY_CYCLES) newBattery = true; 
  uint8_t frame[4];
  LaCrosse::EncodeFrame(frame, newBattery, temperature, false, humidity);
  uint8_t packet[FRAME_LENGTH];
  for(int i = 0; i < 4; i++) packet[i] = frame[i];
  packet[4] = LaCrosse::CalculateCRC(frame, 4);
  SX.Send(packet);
  DPRINTLN("done!");
}

void setup() {

  DBEGIN(115200);
  DPRINTLN("LacrosseSensor");
  DPRINTLN("");

  // BME init
  unsigned status = bme.begin(); 
  if(!status) 
    while(true) {
      delay(1000);
      DPRINTLN("BME280 init failed!");
  }
  DPRINTLN("BME280 init completed!");

  // BME configuration, as suggested in the datasheet for this scenario
  bme.setSampling(Adafruit_BME280::MODE_FORCED,
    Adafruit_BME280::SAMPLING_X1,   // temperature
    Adafruit_BME280::SAMPLING_NONE, // no pressure
    Adafruit_BME280::SAMPLING_X1,   // humidity
    Adafruit_BME280::FILTER_OFF);
  DPRINTLN("BME280 configuration completed!");

  // SX1276 init
  if (!SX.init())
    while(true) {
      delay(1000);
      DPRINTLN("SX127x init failed!");
    }
  DPRINTLN("SX127x init completed!");

  // SX1276 configuration for Lacrosse protocol
  SX.SetupForLaCrosse();
  SX.SetFrequency(frequency);
  SX.SetDataRate(dataRate);
  DPRINTLN("SX127x configuration completed!");

  // Attach function to TRC wakeup
  LowPower.attachInterruptWakeup(RTC_ALARM_WAKEUP, sendPacket, CHANGE);

  DPRINTLN("");
  DPRINTLN("Ready to send...");
  DPRINTLN("");
}

void loop() {

  LowPower.deepSleep(UPDATE_PERIOD * 1000);
}
