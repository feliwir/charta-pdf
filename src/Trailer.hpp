#pragma once
#include "objects/IndirectObject.hpp"
#include <charta/Info.hpp>

namespace charta::pdf
{
class Trailer
{
  public:
    inline void setRoot(IndirectObject root)
    {
        m_root = root;
    }

    inline IndirectObject getRoot() const
    {
        return m_root;
    }

    inline void setInfo(IndirectObject info)
    {
        m_info = info;
    }

    inline std::optional<IndirectObject> getInfo() const
    {
        return m_info;
    }

  private:
    IndirectObject m_root = 0;
    std::optional<IndirectObject> m_info;
};
} // namespace charta::pdf