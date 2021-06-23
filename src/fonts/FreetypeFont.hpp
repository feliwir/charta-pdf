#pragma once
#include <charta/Font.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_FONT_FORMATS_H
#include FT_TRUETYPE_TABLES_H
#include <set>
#include <vector>

namespace charta::pdf
{
class FreetypeFont : public Font
{
  private:
    FontType m_subtype = FontType::Invalid;
    FT_Face m_face;
    const std::vector<uint8_t> m_data;
    std::set<FT_UInt> m_usedGylphs;

    // TrueType / OpenType
    TT_Postscript *m_postScriptTable = nullptr;
    TT_OS2 *m_os2Table = nullptr;
    TT_PCLT *m_pcltTable = nullptr;

  public:
    FreetypeFont(FT_Face face, uint8_t *data, size_t size);
    ~FreetypeFont();

    FontType getSubtype() override;
    short getAscent() override;
    short getDescent() override;
    const char *getFontName() override;
    double getItalicAngle() override;
    std::optional<short> getCapHeight() override;
    std::optional<short> getxHeight() override;

    bool addCodepoint(uint32_t codepoint) override;

  private:
    void loadOpenTypeTables();
};
} // namespace charta::pdf