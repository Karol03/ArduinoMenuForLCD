/**
 * Created by Karol Dudzic @ 2020
 */
#pragma once

#include "Option.hpp"

class EventDispatcher
{
public:
  static void pressOK(options::Option** option)
  {
    *option = (*option)->child(); 
  }

  static void pressCANCEL(options::Option** option)
  {
    *option = (*option)->parent();
  }

  static void pressUP(options::Option** option)
  {
    *option = (*option)->previous();
  }

  static void pressDOWN(options::Option** option)
  {
    *option = (*option)->next();
  }
};
