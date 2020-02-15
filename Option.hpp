/**
 * Created by Karol Dudzic @ 2020
 */
#pragma once

#include <stdint.h>
#include <string.h>

namespace options
{

struct Option
{
  typedef const char* Name;

  Option() : m_size(0), m_options(nullptr), m_parent(nullptr) {}
  Option(Name myName) : m_name(myName), m_size(0), m_options(nullptr), m_parent(nullptr) {}
  Option(Name myName, Option* parent) : m_name(myName), m_size(0), m_options(nullptr), m_parent(parent) {}  
  ~Option() { delete [] m_options; }

  Option& add(Name name)
  {
    Option* oldOptions = m_options;
    m_options = new Option[++m_size];
    copy(m_options, oldOptions, m_size-1);
    m_options[m_size-1] = Option(name);
    return *this;
  }

  Option& operator[](Name name)
  {
    if (strcmp(m_name, name) == 0)
    {
      return *this;
    }
    for (uint8_t i = 0; i < m_size; ++i)
    {
      if (strcmp(m_options[i].m_name, name) == 0)
      {
        return m_options[i];
      }
    }
    return NULL_OPTION;
  }

  Option* next()
  {
    if (m_parent)
    {
      return &(*m_parent)(m_name, 1);
    }
    return &NULL_OPTION;
  }

  Option* previous()
  {
    if (m_parent)
    {
      if (m_parent->m_size > 1)
      {
        return &(*m_parent)(m_name, m_parent->m_size-1);
      }
      return &(*m_parent)[m_name];
    }
    return &NULL_OPTION;
  }

  Option* parent()
  {
    if (m_parent != nullptr)
    {
      if (strcmp(m_parent->m_name, "Menu") != 0)
      {
        return m_parent;
      }
    }
    return this;
  }

  Option* child()
  {
    if (m_size > 0)
    {
      return &m_options[0];
    }
    return this;
  }

  const char* print() const
  {
    return m_name;
  }

private:
  Option& operator()(Name name, uint8_t offset)
  {
    for (uint8_t i = 0; i < m_size; ++i)
    {
      if (strcmp(m_options[i].m_name, name) == 0)
      {
        i += offset;
        if (i < m_size)
        {
          return m_options[i];
        }
        else
        {
          return m_options[i%m_size];
        }
      }
    }
    return NULL_OPTION;
  }

  void copy(Option* dest, Option* src, uint8_t length)
  {
    for (uint8_t i = 0; i < length; i++)
    {
      dest[i] = src[i];
    }
    if (src)
    {
      delete [] src;
    }
  }

private:
  static Option NULL_OPTION;
  Name m_name;
  uint8_t m_size;
  Option* m_options;
  Option* m_parent;
};

}  // namespace options
