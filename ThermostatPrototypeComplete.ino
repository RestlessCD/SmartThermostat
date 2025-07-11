#include "project_config.h"
#include "rotary_encoder.h"
#include "temperature_sensor.h"
#include "display_context.h"
#include "display_manager.h"

#define REFRESH_INTERVAL 5000UL

// Create display context object for passing data to the screen module
DisplayContext g_displayContext;

// Create display manager for managing different display screens
DisplayManager g_displayManager(LCD_RS_PIN, LCD_ENABLE_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN, LCD_COLUMNS, LCD_ROWS);

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  Serial.println(F("Initializing Display..."));
  g_displayManager.begin();
  Serial.println(F("Display Initialized. Initializing sensors..."));
  setupTemperatureSensor(TEMP_SENSOR_PIN, TEMP_SENSOR_TYPE, TEMP_READ_INTERVAL);
  setupEncoder(ENCODER_SW_PIN, ENCODER_DT_PIN, ENCODER_CLK_PIN);
  configureEncoder(TARGET_TEMP_START, TARGET_TEMP_MIN, TARGET_TEMP_MAX, ENCODER_STEPS_PER_CLICK);
  Serial.println(F("System setup complete. Ready for program main loop."));
}

void loop() {
  // Define state variables
  static long lastTargetTemp = 0;
  static unsigned long lastDisplayUpdateTime = 0;

  // Assign current temperature and target temperature to the context object
  g_displayContext.currentTemp = getTemperature();
  g_displayContext.targetTemp = getEncoderPosition();
  g_displayContext.humidity = 0.0f;

  // Assign current time for non-blocking timer
  unsigned long currentTime = millis();

  // Check for state change
  bool targetChanged = (g_displayContext.targetTemp != lastTargetTemp);
  bool timeToRefresh = (currentTime - lastDisplayUpdateTime >= REFRESH_INTERVAL);

  // Print to screen if state has changed or refresh time reached
  if (targetChanged || timeToRefresh) {
    Serial.print(F("Room Temp:"));
    Serial.print(g_displayContext.currentTemp, 1);
    Serial.print(F(" F | Target: "));
    Serial.print(g_displayContext.targetTemp);
    Serial.println(F(" F"));

    g_displayManager.update(g_displayContext);

    // Update values for next loop
    lastTargetTemp = g_displayContext.targetTemp;
    lastDisplayUpdateTime = currentTime;
  }
}
