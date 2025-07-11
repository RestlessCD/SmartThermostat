#include "dashboard_screen.h"
#include "display_context.h"

// Dashboard screen initialization
DashboardScreen::DashboardScreen(LiquidCrystal& lcd)
    : m_lcd(lcd) {

}

// Implementation of the draw override function
void DashboardScreen::draw(const DisplayContext& context) {
  m_lcd.clear(); // Clear screen before drawing
  m_lcd.setCursor(0, 0); // Set cursor at the first column first row

  // Build and print the first line
  String line1 = "Room: " + String(context.currentTemp, 1) + "F";
  m_lcd.print(line1);


  // Build and print the second line
  m_lcd.setCursor(0, 1);
  String line2 = "Target: " + String(context.targetTemp) + "F";
  m_lcd.print(line2);
}