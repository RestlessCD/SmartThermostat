/**
 * @file RotaryEncoder.h
 * @brief Defines a C++ class to manage a KY-040 rotary encoder with a push-button.
 *
 * This class encapsulates the Paul Stoffregen Encoder library and adds features
 * for logical value scaling, settable limits, and push-button handling.
 * It uses a std::unique_ptr to safely manage the lifecycle of the Encoder object,
 * ensuring no memory leaks and safe initialization.
 */

#ifndef ROTARY_ENCODER_H
#define ROTARY_ENCODER_H

#include <Encoder.h>
#include <limits.h>
#include <Arduino.h>

class RotaryEncoder {
public:
    /**
     * @brief Constructs the RotaryEncoder object.
     * @note This only stores pin configuration and does not initialize hardware.
     * @param clkPin The pin for the encoder's CLK signal (must be interrupt-capable).
     * @param dtPin The pin for the encoder's DT signal (must be interrupt-capable).
     * @param swPin The pin for the encoder's push-button switch.
     */
    RotaryEncoder(uint8_t clkPin, uint8_t dtPin, uint8_t swPin);

    // Note: No destructor is needed because std::unique_ptr handles memory cleanup automatically.

    /**
     * @brief Initializes the encoder hardware and pins. Must be called once in setup().
     */
    void begin();

    /**
     * @brief Configures the encoder's behavior with a start position, limits, and step scaling.
     * @note This is the primary configuration function. All parameters are LOGICAL (human-readable) values.
     * @param startLogical The desired starting logical position (e.g., 70 for 70 degrees).
     * @param minLogical The minimum allowed logical position (e.g., 60).
     * @param maxLogical The maximum allowed logical position (e.g., 85).
     * @param steps The number of raw encoder steps that equal one logical step (e.g., 4 for a standard encoder where one click should equal one degree).
     */
    void configure(long startLogical, long minLogical, long maxLogical, int steps);
    
    /**
     * @brief Overloaded version to configure the encoder, using the module's currently set step value.
     * @param startLogical The desired starting logical position.
     * @param minLogical The minimum allowed logical position.
     * @param maxLogical The maximum allowed logical position.
     */
    void configure(long startLogical, long minLogical, long maxLogical);

    /**
     * @brief Overloaded version to configure only the limits, preserving the current logical position.
     * @param minLogical The minimum allowed logical position.
     * @param maxLogical The maximum allowed logical position.
     */
    void configure(long minLogical, long maxLogical);

    /**
     * @brief Disables the min/max limits, allowing the encoder to turn freely.
     * @note The current step scaling is preserved.
     */
    void disableLimits();

    /**
     * @brief Reads the current, limit-enforced, and scaled logical position.
     * @return The current logical position as a long.
     */
    long getPosition();

    /**
     * @brief Directly sets the encoder's current logical position.
     * @note The provided position will be automatically constrained by any active limits.
     * @param logicalPosition The new logical position to set.
     */
    void setPosition(long logicalPosition);

    /**
     * @brief Reads the state of the integrated push-button switch.
     * @note This function should be polled regularly in the main loop. Debouncing is handled internally.
     * @return True if the button is currently being pressed, false otherwise.
     */
    bool getButtonState();

    /**
     * @brief Destructor.
     * @note Automatically cleans up the dynamically allocated Encoder object
     *       to prevent memory leaks.
     */
    ~RotaryEncoder();

private:
    // --- Private Helper Methods ---
    long m_logicalToRaw(long logicalValue);
    long m_rawToLogical(long rawValue);
    long m_enforceLimits(long rawValue);
    void m_writeToHardware(long rawValue);
    long m_readFromHardware(); 

    // --- Member Variables ---
    // Pin configuration
    uint8_t m_clkPin;
    uint8_t m_dtPin;
    uint8_t m_swPin;

    // Pointer for encoder object
    Encoder *m_encoder;

    // State variables for limits and scaling
    bool m_limitsEnabled;
    int m_stepValue;
    long m_rawMin;
    long m_rawMax;

    // State variables for debouncing the push-button
    unsigned long m_lastDebounceTime;
    bool m_lastButtonState;
    bool m_buttonState;
};

#endif // ROTARY_ENCODER_H