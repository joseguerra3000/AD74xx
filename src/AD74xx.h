/**
 * @file AD74xx.h
 * @author Jose Guerra Carmenate (joseguerracarmenate@gmail.com)
 * @brief Header file of AD74xx Driver for Arduino framework
 * 
 * Supported devices: AD7466, AD7467, AD7468, AD7475, AD7476, AD7476A,
 *  AD7477, AD7477A, AD7478, AD7478A, AD7495
 * 
 * @version 0.1
 * @date 2022-08-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <SPI.h>
#include <SoftSPIB.h>

enum AD74xx_TYPE{
  AD7466, // 12
  AD7467, // 10
  AD7468, //  8
  AD7475, // 12
  AD7476, // 12
  AD7476A,// 12
  AD7477, // 10
  AD7477A,// 10 
  AD7478, //  8
  AD7478A,//  8 
  AD7495  // 12
};

/**
 * @brief Driver for AD74xx ADC family.
 * 
 * Supported devices: AD7466, AD7467, AD7468, AD7475, AD7476, AD7476A,
 *  AD7477, AD7477A, AD7478, AD7478A, AD7495
 * 
 */
class AD74xx{
public:
  AD74xx( AD74xx_TYPE type ): m_type(type){};

  /**
   * @brief Specify SPI bus and cs pin for interface.
   * 
   * @note SPI bus must be initialize before call this function.
   * 
   * @param spi pointer to SPIClass object
   * @param cs MCU pin connected to CS pin of ADC
   * @return true Initialization successful
   * @return false Initialization error
   */
  bool begin( SPIClass *spi, int8_t cs );

  /**
   * @brief Specify SPI bus and cs pin for interface.
   * 
   * @note SPI bus must be initialize before call this function.
   * 
   * @param spi SPIClass object
   * @param cs MCU pin connected to CS pin of ADC
   * @return true Initialization successful
   * @return false Initialization error
   */
  bool begin( SPIClass &spi, int8_t cs );

  /**
   * @brief Interface ADC without Hardware SPI bus
   * 
   * @param miso MCU pin connected to MISO pin of ADC  
   * @param sclk MCU pin connected to SCLK pin of ADC
   * @param cs MCU pin connected to CS pin of ADC
   * @return true Initialization successful
   * @return false Initialization error
   */
  bool begin( uint8_t miso, uint8_t sclk, uint8_t cs );

#ifdef ESP32
  /**
   * @brief Specify SPI bus and signal pins for interface.
   * 
   * @note SPI bus must not be initialized. Driver itself do it.
   * 
   * @param spi pointer to SPIClass object
   * @param miso MCU pin connected to MISO pin of ADC  
   * @param sclk MCU pin connected to SCLK pin of ADC
   * @param cs MCU pin connected to CS pin of ADC
   * @return true Initialization successful
   * @return false Initialization error
   */
  bool begin( SPIClass *spi, uint8_t miso, uint8_t sclk, uint8_t cs );

  /**
   * @brief Specify SPI bus and signal pins for interface.
   * 
   * @note SPI bus must not be initialized. Driver itself do it.
   * 
   * @param spi SPIClass object
   * @param miso MCU pin connected to MISO pin of ADC  
   * @param sclk MCU pin connected to SCLK pin of ADC
   * @param cs MCU pin connected to CS pin of ADC
   * @return true Initialization successful
   * @return false Initialization error
   */
  bool begin( SPIClass &spi, uint8_t miso, uint8_t sclk, uint8_t cs );
#endif

  /**
   * @brief Get the ADC resolution in bits
   * 
   * @return int8_t ADC resolution in bits
   */
  inline int8_t getResolution();

  /**
   * @brief Put chip on partial power-down mode.
   * @note Only valid for AD7475 and AD7495
   * 
   * @return true Successful
   * @return false Invalid chip
   */
  bool powerDown();

  /**
   * @brief Power-up de device
   * 
   * @return true Successful
   * @return false Invalid chip
   */
  bool powerUp();

  /**
   * @brief Get the raw value read by the ADC.
   * 
   * @return uint16_t raw value
   */
  uint16_t getRawValue();

  /**
   * @brief Get analog value has voltage. 
   * 
   * @param vref reference voltage used for conversion. 
   * @return float 
   */
  float getVoltage( float vref );

private:
  AD74xx_TYPE m_type; ///!< ADC specific model 
  uint8_t m_cs;       ///!< used cs pin
  uint8_t m_miso,     ///!< used miso pin
          m_sclk;     ///!< used sclk pin

  SPIClass *m_spi;    ///!< pointer to spi bus
  SoftSPIB *m_softspi;///!< SoftwareSPI


};



