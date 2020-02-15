/**
 * Created by Karol Dudzic @ 2020
 */
#pragma once

#include <stdint.h>

struct Button
{
public:
  Button(uint8_t pin, bool mode);
  bool isUniquePress();

private:
  unsigned long m_debounceTime = 0;
  uint8_t m_pin;
  bool m_mode;
  bool m_state;
};
