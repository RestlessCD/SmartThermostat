#include "dashboard_screen.h"
#include <LiquidCrystal.h>

// Dashboard screen initialization
DashboardScreen::DashboardScreen(LiquidCrystal& lcd)
    : m_lcd(lcd), // Initialize lcd reference with passed in lcd object
      m_currentTemp(0.0f), // Initialize current temperature to 0.0f
      m_targetTemp(0) // Initialize target temperature to 0.
{

}

// Implementation of the setData function
void DashboardScreen::setData(float currentTemp, long targetTemp) {
  // Take data and store it into our private member variables
  m_currentTemp = currentTemp;
  m_targetTemp = targetTemp;
}

// Implementation of the draw override function
void DashboardScreen::draw() {

  m_lcd.clear(); // Clear screen before drawing
  m_lcd.setCursor(0, 0); // Set cursor at the first column first row

  // Build and print the first line
  String line1 = "Room: " + String(m_currentTemp, 1) + "F";
  m_lcd.print(line1);


  // Build and print the second line
  m_lcd.setCursor(0, 1);
  String line2 = "Target: " + String(m_targetTemp) + "F";
  m_lcd.print(line2);
}