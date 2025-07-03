#ifndef ROTARY_ENCODER_H
#define ROTARY_ENCODER_H

#include <Arduino.h>
#include <Encoder.h>

// =================================================================
// ---                 PUBLIC API FUNCTIONS                      ---
// =================================================================

/**
 * @brief Initializes the rotary encoder hardware and library.
 * @note Must be called once in the main setup() function. Uses interrupts for high reliability.
 * @param swpin The pin for the encoder's push-button switch. Configured with INPUT_PULLUP.
 * @param dtpin The pin for the encoder's 'DT' (Data) signal. Must be interrupt-capable on UNO (e.g., pin 3).
 * @param clkpin The pin for the encoder's 'CLK' (Clock) signal. Must be interrupt-capable on UNO (e.g., pin 2).
 */
void setupEncoder(uint8_t swpin = 4, uint8_t dtpin = 3, uint8_t clkpin = 2);

/**
 * @brief Configures the encoder's behavior with a start position, limits, and step scaling.
 * @note This is the primary configuration function. All parameters are LOGICAL (human-readable) values.
 * @param start_logical The desired starting logical position (e.g., 70 for 70 degrees).
 * @param min_logical The minimum allowed logical position (e.g., 60).
 * @param max_logical The maximum allowed logical position (e.g., 85).
 * @param steps The number of raw encoder steps that equal one logical step (e.g., 4 for a standard encoder where one click should equal one degree).
 */
void configureEncoder(long start_logical, long min_logical, long max_logical, int steps);

/**
 * @brief Overloaded version to configure the encoder, using the module's currently set step value.
 * @param start_logical The desired starting logical position.
 * @param min_logical The minimum allowed logical position.
 * @param max_logical The maximum allowed logical position.
 */
void configureEncoder(long start_logical, long min_logical, long max_logical);


/**
 * @brief Overloaded version to configure only the limits, preserving the current logical position.
 * @param min_logical The minimum allowed logical position.
 * @param max_logical The maximum allowed logical position.
 */
void configureEncoder(long min_logical, long max_logical);


/**
 * @brief Directly sets the encoder's current logical position.
 * @note The provided position will be automatically constrained by the active limits.
 * @param logicalPosition The new logical position to set.
 */
void setEncoderPosition(long logicalPosition);


/**
 * @brief Reads the current, limit-enforced, and scaled logical position from the encoder.
 * @note This is the primary function for getting the user's desired value in the main loop.
 * @return The current logical position as a `long`. Returns 0 if the module has not been initialized.
 */
long getEncoderPosition();

#endif