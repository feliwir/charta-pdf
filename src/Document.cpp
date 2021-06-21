#include <charta/Document.hpp>

#include "Writer.hpp"
#include "fonts/FreetypeHelper.hpp"
#include <fstream>

bool charta::pdf::Document::saveToFile(std::string_view filepath)
{
    std::ofstream fout(filepath.data(), std::ios::binary);
    if (fout.fail())
    {
        return false;
    }

    return saveToStream(fout);
}

bool charta::pdf::Document::saveToStream(std::ostream &stream)
{
    Writer writer;
    if (!writer.writeHeader(stream, *this))
    {
        return false;
    }

    if (!m_fonts.empty())
    {
        if (!writer.writeFontDefinitions(stream, m_fonts))
        {
        }
    }

    if (!getPages().empty())
    {
        if (!writer.writePageTree(stream, *this))
        {
            return false;
        }
    }

    if (!writer.writeCatalogObject(stream))
    {
        return false;
    }

    if (m_info.has_value())
    {
        if (!writer.writeInfoObject(stream, m_info.value()))
        {
            return false;
        }
    }

    size_t xrefOffset = 0;
    if (!writer.writeXRefTable(stream, *this, xrefOffset))
    {
        return false;
    }

    if (!writer.writeTrailer(stream))
    {
        return false;
    }

    if (!writer.writeXRefTableReference(stream, xrefOffset))
    {
        return false;
    }

    if (!writer.writeEndOfFile(stream))
    {
        return false;
    }

    return true;
}

charta::pdf::Font *charta::pdf::Document::addFontFromFile(std::string_view filepath, bool embed)
{
    std::ifstream fin(filepath.data(), std::ios::binary);
    if (fin.fail())
    {
        return nullptr;
    }

    return addFontFromStream(fin, embed);
}

charta::pdf::Font *charta::pdf::Document::addFontFromStream(std::istream &stream, bool embed)
{
    // Read the data
    stream.seekg(0, std::ios::end);
    auto size = stream.tellg();
    stream.seekg(0, std::ios::beg);

    auto data = new uint8_t[size];
    stream.read((char *)data, size);

    std::vector<uint8_t> data_vec(data, data + size);

    return m_fonts.emplace_back(FreetypeHelper::loadFontFromMemory(data_vec));
}