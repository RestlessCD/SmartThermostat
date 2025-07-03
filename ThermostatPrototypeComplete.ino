#include "rotary_encoder.h"
#include "temperature_sensor.h"

#define steps 4
#define maxTemp 85
#define minTemp 60
#define startTemp 70

void setup() {
  Serial.begin(9600);
  Serial.println(F("Thermostat CLI Test..."));
  setupTemperatureSensor();
  setupEncoder();
  configureEncoder(startTemp, minTemp, maxTemp, steps);
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
