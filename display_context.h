#ifndef DISPLAY_CONTEXT_H
#define DISPLAY_CONTEXT_H

/**
 * 
 * @brief A container for all the data that needs to be rendered by the UI.
 *
 * This struct is populated by the main application loop and is passed by
 * reference to the active screen for display. It ensures the UI system
 * remains a passive "viewer" of the application's state.
 */
struct DisplayContext {
    /** @brief The current temperature read from the sensor (in Fahrenheit). */
    float currentTemp;

    /** @brief The target temperature set by the user via the rotary encoder. */
    long targetTemp;

    /** @brief The current relative humidity. */
    float humidity;
};

#endif // DISPLAY_CONTEXT_H