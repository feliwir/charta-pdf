#pragma once
#include <charta/Font.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <vector>

namespace charta::pdf
{
class FreetypeHelper
{
  public:
    static Font *loadFontFromMemory(uint8_t *data, size_t size);

  private:
    static bool initLibrary();

    static FT_Library s_library;
};
} // namespace charta::pdf