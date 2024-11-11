# LaCrosseSensor
![](https://github.com/lucadentella/LaCrosseSensor/raw/main/images/cover.jpg)

## Description
Homemade temperature and humidity sensor for LaCrosse weather stations.
A complete description of this project is available in a [blog post]() on my website.

In the **Arduino** subfolder, you can find the sketch for the XIAO SAMD21 board.

If you're interested in LaCrosse sensors/stations, I've also designed a bridge between Home Assistant and LaCrosse, **LaCrosseSender**:
- [Github repository](https://github.com/lucadentella/LaCrosseSender)
- [Blog post](https://www.lucadentella.it/en/2024/11/03/da-home-assistant-a-stazione-meteo-la-crosse/) on my website

## Part list
- [Seeed Studio XIAO SAMD21 (Seeeduino Xiao)](https://www.seeedstudio.com/Seeeduino-XIAO-Arduino-Microcontroller-SAMD21-Cortex-M0+-p-4426.html), the brain
- [BME280 module](https://it.aliexpress.com/w/wholesale-bme280-module.html), the sensor
- [SX1276 module](https://it.aliexpress.com/w/wholesale-sx1276-module.html), the talker
- 2xAA battery holder, the power

![](https://github.com/lucadentella/LaCrosseSensor/raw/main/images/project.jpg)

## Connections
- Connect power (VCC or 3.3V) and ground of each module to the battery pack
- BME280 sensor is connected to i2c bus: SDA to Xiao's PIN4 and SCL to PIN5
- SX1276 module is connected to SPI bus: MOSI to Xiao's PIN10, MISO to PIN9, SCK to pin 8, NSS (*ChipSelect*) to PIN7 and RESET to PIN8

![](https://github.com/lucadentella/LaCrosseSensor/raw/main/images/connections.jpg)