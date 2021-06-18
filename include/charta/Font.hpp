#pragma once
#include "FontDescriptor.hpp"
#include "FontType.hpp"
#include <set>
#include <istream>
#include <stdint.h>

namespace charta::pdf
{
class Font
{
  private:
    FontType m_subtype;
    FontDescriptor m_descriptor;
    bool embed;
  public:
    Font(FontType subtype);
};
} // namespace charta::pdf