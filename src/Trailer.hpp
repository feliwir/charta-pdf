#pragma once
#include "ObjectReference.hpp"
#include <charta/Info.hpp>

namespace charta::pdf
{
class Trailer
{
  public:
    inline void setRoot(ObjectReference root)
    {
        m_root = root;
    }

    inline ObjectReference getRoot() const
    {
        return m_root;
    }

    inline void setInfo(ObjectReference info)
    {
        m_info = info;
    }

    inline std::optional<ObjectReference> getInfo() const
    {
        return m_info;
    }

  private:
    ObjectReference m_root = 0;
    std::optional<ObjectReference> m_info;
};
} // namespace charta::pdf