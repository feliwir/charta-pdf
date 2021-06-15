#pragma once
#include "Object.hpp"
#include <map>

namespace charta::pdf
{
// This should probably keep order
class Dictionary
{
  private:
    std::map<NameObject, Object> m_entries;

  public:
    Object &operator[](const NameObject &name)
    {
        return m_entries[name];
    }

    std::map<NameObject, Object>::const_iterator begin() const
    {
        return m_entries.begin();
    }

    std::map<NameObject, Object>::const_iterator end() const
    {
        return m_entries.end();
    }
};
} // namespace charta::pdf