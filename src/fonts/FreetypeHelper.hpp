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
    static Font *loadFontFromMemory(const std::vector<uint8_t> &data);

  private:
    static bool initLibrary();

    static FT_Library s_library;
};
} // namespace charta::pdf