/**
 * @file AD74xx.cpp
 * @author Jose Guerra Carmenate <joseguerracarmenate@gmail.com>
 * @brief Implementation of AD74xx Driver for Arduino framework
 * @version 0.1
 * @date 2022-08-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <Arduino.h>
#include "AD74xx.h"

bool AD74xx::begin( SPIClass *spi, int8_t cs ){
  m_spi = spi;
  m_cs = cs;

  pinMode( m_cs, OUTPUT );
  digitalWrite( m_cs, HIGH );

  if( m_spi != nullptr )
    return true;
}

bool AD74xx::begin( SPIClass &spi, int8_t cs ){
  return begin( &spi, cs );
}

bool AD74xx::begin( uint8_t miso, uint8_t sclk, uint8_t cs ){
  m_miso = miso;
  m_sclk = sclk;
  m_cs = cs;

  m_spi = nullptr;
  
  m_softspi = new SoftSPIB( 17, m_miso, m_sclk );
  m_softspi->begin();
  m_softspi->setBitOrder(MSBFIRST);
  m_softspi->setDataMode(SPI_MODE0);

  pinMode( m_cs, OUTPUT );
  digitalWrite( m_cs, HIGH );

  return true;
}

#ifdef ESP32
bool AD74xx::begin( SPIClass *spi, uint8_t miso, uint8_t sclk, uint8_t cs ){
  m_spi = spi;
  m_sclk = sclk;
  m_miso = miso;
  m_cs = cs;

  pinMode( m_cs, OUTPUT );
  digitalWrite( m_cs, HIGH );

  m_spi->begin( m_sclk, m_miso, -1 );
  return true;
}

bool AD74xx::begin( SPIClass &spi, uint8_t miso, uint8_t sclk, uint8_t cs ){
  return begin( &spi, miso, sclk, cs );
}

inline int8_t AD74xx::getResolution(){

  switch (m_type)
  {
  case AD7466:
  case AD7476:
  case AD7476A:
  case AD7475:
  case AD7495:
    return 12;
  
  case AD7477:
  case AD7477A:
  case AD7467:
    return 10;
  
  case AD7478:
  case AD7468:
  case AD7478A:
    return 8;
  
  default:
    break;
  }


}

bool AD74xx::powerDown(){
  if( m_type != AD7475 && m_type != AD7495 )
    return false;

  if( m_spi ){
    m_spi->beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
    digitalWrite( m_cs, LOW );

    m_spi->transfer(0);
    digitalWrite( m_cs, HIGH ); // CS is brought "High" between 2nd falling edge of SCLK
    
    m_spi->transfer(0);
    m_spi->endTransaction();
  }
  else{
    digitalWrite( m_cs, LOW );
    m_softspi->transfer(0);
    digitalWrite( m_cs, HIGH );
    m_softspi->transfer(0);
  }
  return true;
}

bool AD74xx::powerUp(){
  if( m_type != AD7475 && m_type != AD7495 )
    return false;

  (uint16_t)getRawValue();
  return true;
}

uint16_t AD74xx::getRawValue(){
  uint16_t raw;

  if( m_spi ){
    m_spi->beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
    digitalWrite( m_cs, LOW );

    raw = m_spi->transfer16(0);

    m_spi->endTransaction();
    digitalWrite( m_cs, HIGH );
  }
  else{
    digitalWrite( m_cs, LOW );
    raw = m_softspi->transfer16(0);
    digitalWrite( m_cs, HIGH );
  }

  return raw;
}

float AD74xx::getVoltage( float vref ){
  int8_t res = getResolution();

  return getRawValue()*vref/(1<<res);
}


#endif

