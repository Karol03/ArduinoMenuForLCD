/**
 * Created by Karol Dudzic @ 2020
 */
#include "ButtonDebounce.hpp"

#include "Arduino.h"

#define DEBOUNCE_DELAY 70ul

Button::Button(uint8_t pin, bool mode)
  : m_debounceTime(0)
  , m_pin(pin)
  , m_mode(mode)
  , m_state(mode)
{
  pinMode(m_pin, INPUT);
  digitalWrite(m_pin, mode);
}

bool Button::isUniquePress()
{
  bool state = digitalRead(m_pin);
  if (state != m_state)
  {
    m_debounceTime = millis();
    return false;
  }

  if ((millis() - m_debounceTime) > DEBOUNCE_DELAY)
  {
    if (state != m_state)
    {
      m_state = state;
      return m_state != m_mode;
    }
  }
  return false;
}
