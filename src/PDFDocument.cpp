#include <charta/PDFDocument.hpp>

#include "PDFWriter.hpp"
#include <fstream>

bool charta::pdf::PDFDocument::saveTo(std::string_view filepath)
{
    std::ofstream fout(filepath.data(), std::ios::binary);
    if (fout.fail())
    {
        return false;
    }

    PDFWriter writer;
    if (!writer.writeHeader(fout, *this))
    {
        return false;
    }

    if (!writer.writeCatalogObject(fout))
    {
        return false;
    }

    size_t xrefOffset = 0;
    if (!writer.writeXRefTable(fout, *this, xrefOffset))
    {
        return false;
    }

    if (!writer.writeTrailer(fout, *this))
    {
        return false;
    }

    if (!writer.writeXRefTableReference(fout, xrefOffset))
    {
        return false;
    }

    if (!writer.writeEndOfFile(fout))
    {
        return false;
    }

    return true;
}