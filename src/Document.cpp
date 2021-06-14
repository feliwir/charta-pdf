#include <charta/Document.hpp>

#include "Writer.hpp"
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

    if (!writer.writeCatalogObject(stream))
    {
        return false;
    }

    if(m_info.has_value())
    {
       if(!writer.writeInfoObject(stream, m_info.value()))
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