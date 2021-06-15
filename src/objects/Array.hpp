#pragma once
#include "Object.hpp"
#include <vector>

namespace charta::pdf
{
// This should probably keep order
class Array
{
  private:
    std::vector<Object> m_entries;

  public:
    Array() = default;
    Array(const std::vector<Object>& entries) : m_entries(entries)
    {
    }

    const Object &operator[](size_t index) const
    {
        return m_entries[index];
    }

    Object &emplace_back()
    {
        return m_entries.emplace_back();
    }

    std::vector<Object>::const_iterator begin() const
    {
        return m_entries.begin();
    }

    std::vector<Object>::const_iterator end() const
    {
        return m_entries.end();
    }

    size_t size() const
    {
        return m_entries.size();
    }
};
} // namespace charta::pdf