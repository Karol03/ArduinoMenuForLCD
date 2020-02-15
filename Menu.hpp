/**
 * Created by Karol Dudzic @ 2020
 */
#pragma once

#include "Option.hpp"

struct Menu
{
    Menu() : m_main("Menu") {}

    options::Option& operator[](options::Option::Name name)
    {
        return m_main[name];
    }

    options::Option* build()
    {
      /**
       * Defining main options
       */
      m_main.add("Main")
            .add("Settings")
            .add("Exit");
      /**
       * Defining sub-options
       */
      m_main["Main"].add("New")
                    .add("Load");
      m_main["Settings"].add("Time settings")
                        .add("LCD settings")
                        .add("Alarms");               
      /**
       * Defining sub-sub-options
       */
       m_main["Main"]["New"].add("Easy")
                            .add("Hard");
       m_main["Settings"]["Time settings"].add("Time")
                                          .add("Date")
                                          .add("Time zone");
      /**
       * Above configuration should build menu as below
       * 
       * Menu
       *   Main
       *     New
       *       Easy
       *       Hard
       *     Load
       *   Settings
       *     Time settings
       *       Time
       *       Date
       *       Time zone
       *   Exit
       *   
       */
      return &m_main["Main"];
    }

    options::Option* first()
    {
      /**
       * Dont forget about defining pointer to first menu option 
       */
        return &m_main["Main"];
    }

private:
    options::Option m_main;
};
