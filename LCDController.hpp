/**
 * Created by Karol Dudzic @ 2020
 */
#pragma once

#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

struct LCDController
{
public:
  LCDController() : m_lcd(rs, en, d4, d5, d6, d7)
  {
    m_lcd.begin(16, 2);
  }

  void clear()
  {
    m_lcd.clear();
  }

  void print(const char* firstLine, const char* secondLine)
  {
    clear();
    printFirstLine(firstLine);
    printSecondLine(secondLine);
  }

  void printFirstLine(const char* message)
  {
    m_lcd.setCursor(0, 0);
    m_lcd.print(message);
  }

  void printSecondLine(const char* message)
  {
    m_lcd.setCursor(0, 1);
    m_lcd.print(message);
  }

  void on()
  {
    m_lcd.display();
  }

  void off()
  {
    m_lcd.noDisplay();
  }

private:
  LiquidCrystal m_lcd;
};
