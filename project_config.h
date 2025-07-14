#ifndef PROJECT_CONFIG_H
#define PROJECT_CONFIG_H

// =================================================================
// --- PIN DEFINITIONS ---
// =================================================================
// ROTARY ENCODER PINS
#define ENCODER_SW_PIN 4 // Switch button pin
#define ENCODER_DT_PIN 3 // Data pin (interrupt capable)
#define ENCODER_CLK_PIN 2 // Clock pin (interrupt capable)

// TEMPERATURE SENSOR PINS
#define TEMP_SENSOR_PIN 13 // Data pin for DHT sensor
#define TEMP_SENSOR_TYPE DHT11 // Type of DHT sensor (DHT11, DHT22, etc.)

// =================================================================
// --- DISPLAY SETTINGS ---
// =================================================================
#define LCD_RS_PIN 12
#define LCD_ENABLE_PIN 11
#define LCD_D4_PIN 5
#define LCD_D5_PIN 6
#define LCD_D6_PIN 7
#define LCD_D7_PIN 8
#define LCD_COLUMNS 16
#define LCD_ROWS 2

// =================================================================
// --- THERMOSTAT SETTINGS ---
// =================================================================
#define TARGET_TEMP_MAX 85L // Maximum settable temperature (L for long)
#define TARGET_TEMP_MIN 60L // Minimum settable temperature (L for long)
#define TARGET_TEMP_START 70L // Initial target temperature on startup (L for long)

// =================================================================
// --- BEHAVIOR & TIMING ---
// =================================================================
#define ENCODER_STEPS_PER_CLICK 4 // Raw steps per single "click" of encoder knob (typically 4 means the encoder moves 1 value per click)
#define TEMP_READ_INTERVAL 2000UL // Milliseconds between temperature sensor reads (UL for unsigned long)
#define SERIAL_BAUD_RATE 9600 // For serial monitor communication
#define DISPLAY_REFRESH_INTERVAL 5000UL


#endif