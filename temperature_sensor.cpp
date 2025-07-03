#include "temperature_sensor.h"

// DHT sensor object pointer
static DHT *dht_sensor = nullptr;

// Variables to manage timing and cache the last good reading
static unsigned long lastReadTime = 0;
static unsigned long READ_INTERVAL = 2000;
static float cachedTemperature = -999.0;


// Setup temperature sensor
void setupTemperatureSensor(uint8_t pin, uint8_t type, unsigned long readInterval) {
  // Check for previous dht sensor object
  if (dht_sensor != nullptr) {
    return;
  }

  // Create dht sensor object with provided paramaters
  dht_sensor = new DHT(pin, type);

  // Initialize dht sensor
  dht_sensor->begin();

  READ_INTERVAL = readInterval; // Stores the user assigned interval
  lastReadTime = -READ_INTERVAL; // Forced the first read to be immediate
}


// Get temperature from temperature sensor
float getTemperature(bool isFahrenheit) {
  // Check if sensor object exists
  if (dht_sensor == nullptr) {
    return -999.0;
  }

  // Check if time to take new reading
  unsigned long currentTime = millis();
  if (currentTime - lastReadTime >= READ_INTERVAL) {
    lastReadTime = currentTime;
    float newTemp = dht_sensor->readTemperature(isFahrenheit);
    if (!isnan(newTemp)) {
      cachedTemperature = newTemp;
    }
  }

  return cachedTemperature;
}