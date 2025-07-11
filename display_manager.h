#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include "dashboard_screen.h"
#include <LiquidCrystal.h>
#include <Arduino.h>

// Forward declarations of objects and classes
struct DisplayContext;

class DisplayManager {
public:
    /**
     * @brief Constructor for a parallel LCD.
     * @param rs The pin for the Register Select (RS) line.
     * @param en The pin for the Enable (E) line.
     * @param d4 The pin for the Data 4 line.
     * @param d5 The pin for the Data 5 line.
     * @param d6 The pin for the Data 6 line.
     * @param d7 The pin for the Data 7 line.
     * @param columns The number of columns on the lcd screen
     * @param rows The number of rows on the lcd screen
     */
    DisplayManager(int rs, int en, int d4, int d5, int d6, int d7, int columns, int rows);
    
    /**
     * @brief Initializes the LCD hardware. Must be called once in setup().
     */
    void begin();

    /**
     * @brief The main update function to draw the current screen.
     * @param context The context object containing the data to be displayed.
     */
    void update(const DisplayContext& context);

private:
    LiquidCrystal m_lcd;
    DashboardScreen m_dashboard_screen;
    int m_rspin;
    int m_enpin;
    int m_d4pin;
    int m_d5pin;
    int m_d6pin;
    int m_d7pin;
    int m_columns;
    int m_rows;
};


#endif