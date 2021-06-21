#include "FreetypeHelper.hpp"
#include "FreetypeFont.hpp"

FT_Library charta::pdf::FreetypeHelper::s_library;

bool charta::pdf::FreetypeHelper::initLibrary()
{
    auto error = FT_Init_FreeType(&s_library);
    return error == 0;
}

charta::pdf::Font *charta::pdf::FreetypeHelper::loadFontFromMemory(uint8_t *data, size_t size)
{
    if (!initLibrary())
    {
        return nullptr;
    }

    FT_Face face;
    auto error = FT_New_Memory_Face(s_library, data, /* first byte in memory */
                                    size,            /* size in bytes        */
                                    0,               /* face_index           */
                                    &face);

    if (error)
    {
        return nullptr;
    }

    return new FreetypeFont(face, data, size);
}