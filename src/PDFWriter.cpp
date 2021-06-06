#include "PDFWriter.hpp"

bool charta::pdf::PDFWriter::writeHeader(std::ostream &stream, const PDFDocument &doc)
{
    // Write a comment containing the PDF version
    const std::string version_comment = "PDF-" + doc.getVersion().toString();
    if (!writeComment(stream, version_comment))
    {
        return false;
    }

    // Indicates that this PDF contains binary data
    const std::string binary_comment = "\xbd\xbe\xbc";
    if (!writeComment(stream, binary_comment))
    {
        return false;
    }

    return true;
}

bool charta::pdf::PDFWriter::writeEndOfFile(std::ostream &stream)
{
    // Indicates that this PDF ends
    if (!writeComment(stream, "%EOF"))
    {
        return false;
    }

    return true;
}

bool charta::pdf::PDFWriter::writeXRefTable(std::ostream &stream, const PDFDocument &doc, size_t &tablePos)
{
    tablePos = stream.tellp();

    return writeKeyword(stream, "xref");
}

bool charta::pdf::PDFWriter::writeXRefTableReference(std::ostream &stream, const size_t tablePos)
{
    if (!writeKeyword(stream, "startxref"))
    {
        return false;
    }

    if (!writeInteger(stream, tablePos))
    {
        return false;
    }

    return writeNewLine(stream);
}

bool charta::pdf::PDFWriter::writeTrailer(std::ostream &stream, const PDFDocument &doc)
{
    if (!writeKeyword(stream, "trailer"))
    {
        return false;
    }

    std::map<std::string, std::string> trailerDict;
    trailerDict["Size"] = "0";

    if (!writeDictionary(stream, trailerDict))
    {
        return false;
    }

    return true;
}

bool charta::pdf::PDFWriter::writeInteger(std::ostream &stream, int value)
{
    std::string value_str = std::to_string(value);
    stream.write(value_str.data(), value_str.size());

    return !stream.bad();
}

bool charta::pdf::PDFWriter::writeComment(std::ostream &stream, std::string_view comment)
{
    stream.put('%');
    stream.write(comment.data(), comment.size());

    return writeNewLine(stream);
}

bool charta::pdf::PDFWriter::writeKeyword(std::ostream &stream, std::string_view keyword)
{
    stream.write(keyword.data(), keyword.size());

    return writeNewLine(stream);
}

bool charta::pdf::PDFWriter::writeNewLine(std::ostream &stream)
{
    stream.write("\r\n", 2);
    return !stream.bad();
}

bool charta::pdf::PDFWriter::writeDictionary(std::ostream &stream, const std::map<std::string, std::string> &dict)
{
    if (!writeKeyword(stream, "<<"))
    {
        return false;
    }

    return writeKeyword(stream, ">>");
}