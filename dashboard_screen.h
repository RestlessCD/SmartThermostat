#ifndef DASHBOARD_SCREEN_H
#define DASHBOARD_SCREEN_H

#include "base_screen.h"
#include <LiquidCrystal.h>

class DashboardScreen : public BaseScreen {
public:

    /**
     * @brief The constructor. It's called when a DashboardScreen object is created.
     * @param lcd A reference to the physical LCD object that this screen will draw on.
     */
    DashboardScreen(LiquidCrystal& lcd);
    
    /**
     * @brief This function fulfills the contract from BaseScreen. It must have the
     *        exact same signature: no arguments and returns void. The 'override'
     *        keyword is a safety check that tells the compiler to verify this.
     */
    virtual void draw(const DisplayContext& context) override;


private:

    /**
     * @brief A reference to the single, shared LCD object. This screen does not
     *        own the LCD; it just holds a "link" to it.
     */
    LiquidCrystal& m_lcd;

    /**
     * @brief Member variables (prefixed with 'm_') to store the state.
     */
    float m_currentTemp;
    long m_targetTemp;
};


#endif