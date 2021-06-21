#pragma once
#include <charta/Font.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_FONT_FORMATS_H

namespace charta::pdf
{
class FreetypeFont : public Font
{
  private:
    FontType m_subtype = FontType::Invalid;
    FT_Face m_face;

  public:
    FreetypeFont(FT_Face face);

    FontType getSubtype() override;
    short getAscent() override;
    short getDescent() override;
    std::string_view getFontName() override;
};
} // namespace charta::pdf