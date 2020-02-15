/**
 * The demonstration of simple menu build on arduino/ atmega microcontrollers.
 * Menu structure has been defined in  Menu.hpp/ options::Option* build() method.
 * You can define own structure based on prepared sample.
 * 
 * To run and try above example under own device it is needed to connect LCD and four buttons as well:
 * 
 * LCD : rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
 * BUTTONS : down = 2, up = 3, cancel = 4, ok = 5
 * 
 * Author Karol Dudzic
 * Contact karoldudzic03@gmail.com
 */
 
#include "ButtonDebounce.hpp"
#include "EventDispatcher.hpp"
#include "LCDController.hpp"
#include "Menu.hpp"

#define PIN_DOWN    2
#define PIN_UP      3
#define PIN_CANCEL  4
#define PIN_OK      5

LCDController lcd;
Menu menu;
options::Option* current{NULL};

Button buttonUp(PIN_UP, HIGH);
Button buttonDown(PIN_DOWN, HIGH);
Button buttonOk(PIN_OK, HIGH);
Button buttonCancel(PIN_CANCEL, HIGH);

bool isLCDRefreshNeeded()
{
  if (buttonUp.isUniquePress())
  {
    EventDispatcher::pressUP(&current);
    return true;
  }
  else if (buttonDown.isUniquePress())
  {
    EventDispatcher::pressDOWN(&current);
    return true;
  }
  else if (buttonOk.isUniquePress())
  {
    EventDispatcher::pressOK(&current);
    return true;
  }
  else if (buttonCancel.isUniquePress())
  {
    EventDispatcher::pressCANCEL(&current);
    return true;
  }
  return false;
}

void setup()
{
  Serial.println("Hello world");
  current = menu.build();
}

void loop()
{
  if (isLCDRefreshNeeded())
  {
    lcd.clear();
    lcd.printFirstLine(current->print());
  }
}
