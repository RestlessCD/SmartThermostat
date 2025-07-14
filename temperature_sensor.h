#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H

#include <Arduino.h>
#include <DHT.h>

class TemperatureSensor {
public:
    /**
     * @brief Constructor. Sets up the sensor's physical configuration.
     * @param pin The digital pin the DHT sensor is connected to.
     * @param type The type of DHT sensor (e.g., DHT11, DHT22).
     */
    TemperatureSensor(uint8_t pin, uint8_t type);

    /**
     * @brief Initializes the sensor hardware and sets the read behavior.
     * @note Can be called again to change the read interval.
     * @param readInterval The minimum time in milliseconds between sensor reads. Defaults to 2000ms.
     */
    void begin(unsigned long readInterval = 2000);

    /**
     * @brief Gets the current temperature reading.
     * @note This function is non-blocking and returns a cached value if the read interval has not passed.
     * @param isFahrenheit True for Fahrenheit, false for Celsius. Defaults to true.
     * @return The temperature as a float. Returns a special value on error or if not initialized.
     */
    float getTemperature(bool isFahrenheit = true);

private:
    // State variables to store the hardware configuration
    uint8_t m_pin;
    uint8_t m_type;

    // DHT object decleration for ownership
    DHT m_dht;

    // Internal state for non-blocking timer and cache
    unsigned long m_readInterval;
    unsigned long m_lastReadTime;
    float m_cachedTemperature;
};

#endif