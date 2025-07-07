#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAHER_H

#include "dashboard_screen.h"
#include <LiquidCrystal.h>

class DisplayManager {
public:
    
    DisplayManager()
    
    void begin();

    void update();

private:
    LiquidCrystal m_lcd;
    DashboardScreen m_dashboard_screen;
    uint8_t m_rspin;
    uint8_t m_enpin;
    uint8_t m_d4pin;
    uint8_t m_d5pin;
    uint8_t m_d6pin;
    uint8_t m_d7pin;
}



#endif