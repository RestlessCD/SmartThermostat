#include "project_config.h"
#include "rotary_encoder.h"
#include "temperature_sensor.h"

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  Serial.println(F("Thermostat CLI Test..."));
  setupTemperatureSensor(TEMP_SENSOR_PIN, TEMP_SENSOR_TYPE, TEMP_READ_INTERVAL);
  setupEncoder(ENCODER_SW_PIN, ENCODER_DT_PIN, ENCODER_CLK_PIN);
  configureEncoder(TARGET_TEMP_START, TARGET_TEMP_MIN, TARGET_TEMP_MAX, ENCODER_STEPS_PER_CLICK);
}

void loop() {
  static long lastTargetTemp = 0;

  float currentTemp = getTemperature();
  long targetTemp = getEncoderPosition();

  if (targetTemp != lastTargetTemp) {
    Serial.print(F("Room:"));
    Serial.print(currentTemp, 1);
    Serial.print(F(" F | Target: "));
    Serial.print(targetTemp);
    Serial.println(F(" F"));
    lastTargetTemp = targetTemp;
  }
}
