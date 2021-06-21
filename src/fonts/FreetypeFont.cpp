#include "FreetypeFont.hpp"
#include <iostream>

charta::pdf::FreetypeFont::FreetypeFont(FT_Face face) : m_face(face)
{
    auto type = std::string(FT_Get_Font_Format(face));

    if (type == "TrueType")
    {
        m_subtype = FontType::TrueType;
    }
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

std::string_view charta::pdf::FreetypeFont::getFontName()
{
    auto name = FT_Get_Postscript_Name(m_face);
    return name;
}