#include "FreetypeFont.hpp"
#include <iostream>

charta::pdf::FreetypeFont::FreetypeFont(FT_Face face, uint8_t *data, size_t size)
    : m_face(face), m_data(data, data + size)
{
    auto type = std::string(FT_Get_Font_Format(face));

    if (type == "TrueType")
    {
        m_subtype = FontType::TrueType;
    }

    switch (m_subtype)
    {
    case FontType::TrueType:
        loadOpenTypeTables();
        break;
    }
}

void charta::pdf::FreetypeFont::loadOpenTypeTables()
{
    m_postScriptTable = static_cast<TT_Postscript *>(FT_Get_Sfnt_Table(m_face, ft_sfnt_post));

    m_os2Table = static_cast<TT_OS2 *>(FT_Get_Sfnt_Table(m_face, ft_sfnt_os2));

    m_pcltTable = static_cast<TT_PCLT *>(FT_Get_Sfnt_Table(m_face, ft_sfnt_pclt));
}

charta::pdf::FreetypeFont::~FreetypeFont()
{
    FT_Done_Face(m_face);
}

charta::pdf::FontType charta::pdf::FreetypeFont::getSubtype()
{
    return m_subtype;
}

short charta::pdf::FreetypeFont::getAscent()
{
    return m_face->ascender;
}

short charta::pdf::FreetypeFont::getDescent()
{
    return m_face->descender;
}

const char *charta::pdf::FreetypeFont::getFontName()
{
    const char *name = FT_Get_Postscript_Name(m_face);
    return name;
}

double charta::pdf::FreetypeFont::getItalicAngle()
{
    return (m_postScriptTable != nullptr) ? (m_postScriptTable->italicAngle / double(1 << 16)) : 0.0;
}

std::optional<short> charta::pdf::FreetypeFont::getCapHeight()
{
    if (m_os2Table != nullptr)
    {
        return m_os2Table->sCapHeight;
    }
    if (m_pcltTable != nullptr)
    {
        return m_pcltTable->CapHeight;
    }
    return {};
}

std::optional<short> charta::pdf::FreetypeFont::getxHeight()
{
    if (m_os2Table != nullptr)
    {
        return m_os2Table->sxHeight;
    }
    if (m_pcltTable != nullptr)
    {
        return m_pcltTable->xHeight;
    }
    return {};
}