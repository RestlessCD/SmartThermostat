#include "temperature_sensor.h"

// Constructor for temperature sensor
TemperatureSensor::TemperatureSensor(uint8_t pin, uint8_t type)
    : m_dht(pin, type),
      m_pin(pin),
      m_type(type),
      m_lastReadTime(0),
      m_cachedTemperature(-999.0f) {

}

void TemperatureSensor::begin(unsigned long readInterval) {
  // Set read interval
  m_readInterval = readInterval;

  m_dht.begin();

  m_lastReadTime = -m_readInterval; // Force first read
}

float TemperatureSensor::getTemperature(bool isFahrenheit) {
  // Check if time to take new reading
  unsigned long currentTime = millis();
  if (currentTime - m_lastReadTime >= m_readInterval) {
    m_lastReadTime = currentTime; // Set read time state variable equal to current time
    float newTemp = m_dht.readTemperature(isFahrenheit); // Get temperature from sensor
    
    // Check if temperature is valid
    if (!isnan(newTemp)) {
      m_cachedTemperature = newTemp;
    }
  }

  // Return new temperature or cached temperature
  return m_cachedTemperature;
}

