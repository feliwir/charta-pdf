#pragma once
#include "FontDescriptor.hpp"
#include "FontType.hpp"
#include <istream>
#include <set>
#include <stdint.h>

namespace charta::pdf
{
class Font
{
  protected:
    FontDescriptor m_descriptor;
    bool m_embed;

  public:
    virtual short getAscent() = 0;
    virtual short getDescent() = 0;
    virtual FontType getSubtype() = 0;
    virtual std::string_view getFontName() = 0;
};
} // namespace charta::pdf