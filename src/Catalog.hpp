#pragma once
#include "objects/IndirectObject.hpp"
#include <optional>

namespace charta::pdf
{
class Catalog
{
  public:
    inline void setPages(IndirectObject root)
    {
        m_pages = root;
    }

    inline std::optional<IndirectObject> getPages() const
    {
        return m_pages;
    }

  private:
    std::optional<IndirectObject> m_pages;
};
} // namespace charta::pdf