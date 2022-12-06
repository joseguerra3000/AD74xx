/**
 * @file ADC74xx_simple.ino
 * @author Jose Guerra Carmenate <joseguerracarmenate@gmail.com>
 * @brief ADC74xx driver (Example 1)
 * 
 * Use of ADC74xx with SPI port on ESP32. Use Serial plotter or Serial monitor on Arduino IDE for see values.
 * On PlatformIO use serial monitor.
 * 
 * Tested with: 
 *  - Heltec Wireless Stick, Heltec Wireless Stick Lite
 * 
 * @version 0.1
 * @date 2022-08-31
 * 
 * @copyright Copyright (c) 2022
 * 
 *
 */
#include <Arduino.h>
#include <AD74xx.h>
#include <SPI.h>

#define ADC_SCK  22 /// ADC SCK pin
#define ADC_MISO 21 /// ADC MISO pin
#define ADC_SS   23 /// ADC CS pin

AD74xx adc( AD74xx_TYPE::AD7466 );

void setup(){
  Serial.begin( 115200 );

  Serial.println("Init SPI");
  SPI.begin( ADC_SCK, ADC_MISO, 17, ADC_SS ); // initialization of SPI port

  Serial.println("Init ADC");
  adc.begin( SPI, ADC_SS );
}

void loop(){
  int16_t raw = adc.getRawValue();
  Serial.println(raw);
  delayMicroseconds(125);
}