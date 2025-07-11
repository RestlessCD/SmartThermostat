#include "dashboard_screen.h"
#include "display_context.h"

// Dashboard screen initialization
DashboardScreen::DashboardScreen(LiquidCrystal& lcd)
    : m_lcd(lcd),
      m_lastDisplayedTemp(-999.0f),
      m_lastDisplayedTarget(-999),
      m_firstDraw(true) {

}

// Implementation of the draw override function
void DashboardScreen::draw(const DisplayContext& context) {
  // Check for first draw to print initial layout
  if (m_firstDraw) {
    printInitialLayout();
    m_firstDraw = false;
  }

  // Selectively update room temperature
  if ((int)(context.currentTemp * 10) != (int)(m_lastDisplayedTemp * 10)) {
    m_lcd.setCursor(6, 0); // Position cursor after "Room: "
    m_lcd.print(context.currentTemp, 1);
    m_lcd.print(" "); // Add spacers after overwrite for longer numbers

    m_lastDisplayedTemp = context.currentTemp;
  }

  // Selectively update target temperature
  if (context.targetTemp != m_lastDisplayedTarget) {
    m_lcd.setCursor(8, 1); // Position curosr after "Target: "
    m_lcd.print(context.targetTemp);
    m_lcd.print("   "); // Print extra space to overwrite longer numbers

    m_lastDisplayedTarget = context.targetTemp;
  }
}


void DashboardScreen::printInitialLayout() {
  m_lcd.clear();

  // Print line 1 static text
  m_lcd.setCursor(0, 0);
  m_lcd.print(F("Room:     F")); // Leave enough room for the numbers

  // Print line 2 static text
  m_lcd.setCursor(0, 1);
  m_lcd.print(F("Target:     F")); // Leave spaces for the numbers
}