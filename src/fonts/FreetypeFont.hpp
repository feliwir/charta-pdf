#pragma once
#include <charta/Font.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_FONT_FORMATS_H
#include <vector>

namespace charta::pdf
{
class FreetypeFont : public Font
{
  private:
    FontType m_subtype = FontType::Invalid;
    FT_Face m_face;
    const std::vector<uint8_t> m_data;

  public:
    FreetypeFont(FT_Face face, uint8_t* data, size_t size);
    ~FreetypeFont();

    FontType getSubtype() override;
    short getAscent() override;
    short getDescent() override;
    const char* getFontName() override;
};
} // namespace charta::pdf