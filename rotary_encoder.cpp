#include "rotary_encoder.h"

// Debouncing delay for encoder button
#define DEBOUNCE_DELAY 50 // 50 milliseconds

RotaryEncoder::RotaryEncoder(uint8_t clkPin, uint8_t dtPin, uint8_t swPin) 
    : m_clkPin(clkPin),
      m_dtPin(dtPin),
      m_swPin(swPin),
      m_encoder(nullptr),
      m_limitsEnabled(false),
      m_stepValue(1),
      m_rawMin(LONG_MIN),
      m_rawMax(LONG_MAX),
      m_lastDebounceTime(0),
      m_lastButtonState(HIGH),
      m_buttonState(HIGH) {

}


void RotaryEncoder::begin() {
  // Set pinmode for the arduino
  pinMode(m_swPin, INPUT_PULLUP);

  // Create Encoder object and give ownership to smart pointer
  m_encoder = new Encoder(m_dtPin, m_clkPin);
}


// CONFIGURE ENCODER FUNCTIONS


// Encoder configure master function
void RotaryEncoder::configure(long startLogical, long minLogical, long maxLogical, int steps) {
  if (!m_encoder) return;

  m_stepValue = (steps == 0) ? 1 : steps; // Set step value
  m_limitsEnabled = true; // Enable limits

  // Convert logical values to internal raw values
  m_rawMin = m_logicalToRaw(minLogical);
  m_rawMax = m_logicalToRaw(maxLogical);

  // Set starting position of encoder with limits enforced
  m_writeToHardware(m_enforceLimits(m_logicalToRaw(startLogical)));
}

// Three paramater overloaded function
void RotaryEncoder::configure(long startLogical, long minLogical, long maxLogical) {
  // Call encoder master function
  configure(startLogical, minLogical, maxLogical, m_stepValue);
}

// Two parameter overloaded function
void RotaryEncoder::configure(long minLogical, long maxLogical) {
  if (!m_encoder) return;

  // Get current logical position for passing to master function
  long currentLogical = m_rawToLogical(m_readFromHardware());

  // Call master function
  configure(currentLogical, minLogical, maxLogical, m_stepValue);
}

// Set encoder position function
void RotaryEncoder::setPosition(long logicalPosition) {
  if (!m_encoder) return;


  // Set encoder position
  m_writeToHardware(m_enforceLimits(m_logicalToRaw(logicalPosition)));
}

// Get encoder position function
long RotaryEncoder::getPosition() {
  if (!m_encoder) return -1;

  // Read raw value from hardware
  long rawPos = m_readFromHardware();

  // Pass raw value through limit filter
  long correctedRawPos = m_enforceLimits(rawPos);

  // Correct position if hardware position has drifted out of limits
  if (rawPos != correctedRawPos) {
    m_writeToHardware(correctedRawPos);
  }

  return m_rawToLogical(correctedRawPos);
}

// Disable limits function
void RotaryEncoder::disableLimits() {
  // Set limits
  m_limitsEnabled = false;
  m_rawMin = LONG_MIN;
  m_rawMax = LONG_MAX;
}

// Button press function
bool RotaryEncoder::getButtonState() {
  // Read raw state of the switch
  bool reading = digitalRead(m_swPin);

  // Check if state has changed since last check
  if (reading != m_lastButtonState) {
    // Reset debouncing timer
    m_lastDebounceTime = millis();
  }

  // Check if state has been stable for longer than our debouncing delay
  if ((millis() - m_lastDebounceTime) > DEBOUNCE_DELAY) {
    // If state has been stable, update official button state
    if (reading != m_buttonState) {
      m_buttonState = reading;
      // We could add logic here for "on press" or "on release" events if needed later.
    }
  }

  // Update last raw state for loop
  m_lastButtonState = reading;

  // Return official debounced state
  // Using INPUT_PULLUP, LOW means pressed
  return (m_buttonState == LOW);
}

// --- Destructor ---
// This is called automatically when the RotaryEncoder object goes out of scope,
// ensuring that the memory we allocated with 'new' in the begin() method
// is properly freed.
RotaryEncoder::~RotaryEncoder() {
  // Deletes encoder object when class is destroyed to prevent memory leaks
  delete m_encoder;
}


// PRIVATE HELPER FUNCTIONS //

// Converts logical values to raw values
long RotaryEncoder::m_logicalToRaw(long logicalValue) {
  return logicalValue * m_stepValue;
}

// Converts raw values to logical values
long RotaryEncoder::m_rawToLogical(long rawValue) {
  return rawValue / m_stepValue;
}

// Enforces limits and returns a corrected, valid raw value
long RotaryEncoder::m_enforceLimits(long rawValue) {
  if (m_limitsEnabled) {
    if (rawValue < m_rawMin) return m_rawMin;
    if (rawValue > m_rawMax) return m_rawMax;
  }
  return rawValue;
}

// Reads raw positional data from rotary encoder and returns it
long RotaryEncoder::m_readFromHardware() {
  if (!m_encoder) return -999;
  return m_encoder->read();
}

// Writes raw positional data to the rotary encoder
void RotaryEncoder::m_writeToHardware(long rawValue) {
  if (!m_encoder) return;
  return m_encoder->write(rawValue);
}