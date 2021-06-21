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