#include "display_manager.h"
#include "display_context.h"

DisplayManager::DisplayManager(int rs, int en, int d4, int d5, int d6, int d7, int columns, int rows)
    : m_lcd(rs, en, d4, d5, d6, d7),
      m_dashboard_screen(m_lcd),
      m_columns(columns),
      m_rows(rows) {

}


void DisplayManager::begin() {
  m_lcd.begin(m_columns, m_rows);
  m_lcd.clear();
  m_lcd.print("System Ready.");
  delay(1000);
}


void DisplayManager::update(const DisplayContext& context) {
  // Call dashboard screen draw function with context object
  m_dashboard_screen.draw(context);
}