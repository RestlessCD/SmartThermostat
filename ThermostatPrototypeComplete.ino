#include "project_config.h"
#include "rotary_encoder.h"
#include "temperature_sensor.h"

#define REFRESH_INTERVAL 5000UL

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  Serial.println(F("Thermostat CLI Test..."));
  setupTemperatureSensor(TEMP_SENSOR_PIN, TEMP_SENSOR_TYPE, TEMP_READ_INTERVAL);
  setupEncoder(ENCODER_SW_PIN, ENCODER_DT_PIN, ENCODER_CLK_PIN);
  configureEncoder(TARGET_TEMP_START, TARGET_TEMP_MIN, TARGET_TEMP_MAX, ENCODER_STEPS_PER_CLICK);
}

void loop() {
  // Define state variables
  static long lastTargetTemp = 0;
  static unsigned long lastDisplayUpdateTime = 0;

  // Get all current hardware variables
  float currentTemp = getTemperature();
  long currentTargetTemp = getEncoderPosition();
  unsigned long currentTime = millis();

  // Check for state change
  bool targetChanged = (currentTargetTemp != lastTargetTemp);
  bool timeToRefresh = (currentTime - lastDisplayUpdateTime >= REFRESH_INTERVAL);

  // Print to screen if state has changed or refresh time reached
  if (targetChanged || timeToRefresh) {
    Serial.print(F("Room Temp:"));
    Serial.print(currentTemp, 1);
    Serial.print(F(" F | Target: "));
    Serial.print(currentTargetTemp);
    Serial.println(F(" F"));
    lastTargetTemp = currentTargetTemp;
    lastDisplayUpdateTime = currentTime;
  }
}
