#pragma once
#include "FontDescriptor.hpp"
#include "FontType.hpp"
#include <istream>
#include <optional>
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
    virtual ~Font(){};

    virtual short getAscent() = 0;
    virtual short getDescent() = 0;
    virtual FontType getSubtype() = 0;
    virtual const char *getFontName() = 0;

    virtual double getItalicAngle() = 0;
    virtual std::optional<short> getCapHeight() = 0;
    virtual std::optional<short> getxHeight() = 0;

    virtual bool addCodepoint(uint32_t codepoint) = 0;
};
} // namespace charta::pdf