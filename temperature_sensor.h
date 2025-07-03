#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H

#include <Arduino.h>
#include <DHT.h>

// =================================================================
// ---                 PUBLIC API FUNCTIONS                      ---
// =================================================================

/**
 * @brief Initializes the temperature sensor module.
 * @note Must be called once in the main setup() function before any other functions are used.
 * @param pin The Arduino digital pin the DHT sensor's data line is connected to. Defaults to pin 7.
 * @param type The type of DHT sensor being used (e.g., DHT11, DHT22). Defaults to DHT11.
 * @param readInterval The minimum time in milliseconds between sensor reads. Defaults to 2000ms.
 */
void setupTemperatureSensor(uint8_t pin = 13, uint8_t type = DHT11, unsigned long readInterval = 2000);


/**
 * @brief Reads the current temperature from the sensor.
 * @note This function handles all internal logic, including error checking.
 * @param isFahrenheit A boolean to select the temperature scale. `true` for Fahrenheit, `false` for Celsius. Defaults to true.
 * @return The current temperature as a float. Returns -999.0f if the sensor is not initialized or if the reading fails. Returns the last known good value if read interval has not been passed.
 */
float getTemperature(bool isFahrenheit = true);

#endif