#include "rotary_encoder.h"

// === Private Helper Function Declarations (Forward Declarations) ===
static long _logicalToRaw(long logicalValue);
static long _rawToLogical(long rawValue);
static long _enforceLimits(long rawValue);
static long _readFromHardware();
static void _writeToHardware(long rawValue);


// === Private State Variables ===

// Rotary encoder object pointer
static Encoder *encoder = nullptr;

// Encoder raw limit values
static long g_rawEncoderMin = LONG_MIN;
static long g_rawEncoderMax = LONG_MAX;

// Encoder limit enabled flag (true = limits are enabled)
static bool g_limitsEnabled = false;

// Encoder step value (defaults to 1, encoder typically moves 4 times per click, so 4 is a good value if you want it to move 1 value per click)
static int g_stepValue = 1;


// === Public API Functions ===

// Setup rotary encoder function
void setupEncoder(uint8_t swpin, uint8_t dtpin, uint8_t clkpin) {
  // Check for existing encoder object
  if (encoder != nullptr) return;

  // Configure switch pin
  pinMode(swpin, INPUT_PULLUP);

  // Create new encoder object with paramaters
  encoder = new Encoder(dtpin, clkpin);
}

// CONFIGURE ENCODER FUNCTIONS

// Configure encoder master function
void configureEncoder(long start_logical, long min_logical, long max_logical, int steps) {
  if (encoder == nullptr) return; // Check for valid object
  
  g_stepValue = (steps == 0) ? 1 : steps; // Set step value
  g_limitsEnabled = true; // Enable limits

  // Convert logical values to internal raw values
  g_rawEncoderMin = _logicalToRaw(min_logical);
  g_rawEncoderMax = _logicalToRaw(max_logical);

  // Set starting position of encoder with limits enforced
  _writeToHardware(_enforceLimits(_logicalToRaw(start_logical)));
}

// Three paramater configuration overloaded function
void configureEncoder(long start_logical, long min_logical, long max_logical) {
  // Call encoder master function
  configureEncoder(start_logical, min_logical, max_logical, g_stepValue);
}

// Two paramater configuration overloaded function
void configureEncoder(long min_logical, long max_logical) {
  if (encoder == nullptr) return;

  // Current logical for passing to master function
  long currentLogical = _rawToLogical(_readFromHardware());

  // Call master function
  configureEncoder(currentLogical, min_logical, max_logical, g_stepValue);
}

// Set rotary encoder to position
void setEncoderPosition(long logicalPosition) {
  if (encoder == nullptr) return;

  // Set encoder position
  _writeToHardware(_enforceLimits(_logicalToRaw(logicalPosition)));
}

// Get rotary encoder position
long getEncoderPosition() {
  if (encoder == nullptr) return 0;
  
  // Read raw value from hardware
  long rawPos = _readFromHardware();

  // Pass raw value through limit filter
  long correctedRawPos = _enforceLimits(rawPos);

  // Correct position if hardware position has drifted out of limits
  if (rawPos != correctedRawPos) {
    _writeToHardware(correctedRawPos);
  }

  return _rawToLogical(correctedRawPos);
}

// Converts logical values into raw stepped values
static long _logicalToRaw(long logicalValue) {
  return logicalValue * g_stepValue;
}

// Converts raw stepped values into logical values
static long _rawToLogical(long rawValue) {
  return rawValue / g_stepValue;
}

// Enforces limits and returns a corrected, valid raw value
static long _enforceLimits(long rawValue) {
  if (g_limitsEnabled) {
    if (rawValue < g_rawEncoderMin) return g_rawEncoderMin;
    if (rawValue > g_rawEncoderMax) return g_rawEncoderMax;
  }
  return rawValue;
}

// Reads raw positonal data from the rotary encoder and returns it as a raw stepped value
static long _readFromHardware() {
  if (encoder == nullptr) return -999;
  return encoder->read();
}

// Writes positional data to the rotary encoder as a raw stepped value
static void _writeToHardware(long rawValue) {
  if (encoder == nullptr) return;
  encoder->write(rawValue);
}