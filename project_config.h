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

// LCD PINS
#define
#define
#define
#define
#define
#define

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


#endif