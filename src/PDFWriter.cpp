#include "PDFWriter.hpp"
#include "PDFLiterals.hpp"

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
    if (!writeComment(stream, PDF_COMMENT_EOF))
    {
        return false;
    }

    return true;
}

bool charta::pdf::PDFWriter::writeXRefTable(std::ostream &stream, const PDFDocument &doc, size_t &tablePos)
{
    tablePos = stream.tellp();

    return writeKeyword(stream, PDF_KEYWORD_XREF);
}

bool charta::pdf::PDFWriter::writeXRefTableReference(std::ostream &stream, const size_t tablePos)
{
    if (!writeKeyword(stream, PDF_KEYWORD_STARTXREF))
    {
        return false;
    }

    if (!writeInteger(stream, tablePos))
    {
        return false;
    }

    return writeNewLine(stream);
}

bool charta::pdf::PDFWriter::writeCatalogObject(std::ostream &stream)
{
    auto &object = startWriteObject(stream);

    std::map<std::string, std::string> trailerDict;
    trailerDict[PDF_DICT_KEY_TYPE] = PDF_DICT_VALUE_CATALOG;

    if (!writeDictionary(stream, trailerDict))
    {
        return false;
    }

    return endWriteObject(stream);
}

bool charta::pdf::PDFWriter::writeTrailer(std::ostream &stream, const PDFDocument &doc)
{
    if (!writeKeyword(stream, PDF_KEYWORD_TRAILER))
    {
        return false;
    }

    std::map<std::string, std::string> trailerDict;
    trailerDict[PDF_DICT_KEY_SIZE] = "0";

    if (!writeDictionary(stream, trailerDict))
    {
        return false;
    }

    return true;
}

bool charta::pdf::PDFWriter::writeInteger(std::ostream &stream, int value, char seperator)
{
    std::string value_str = std::to_string(value);
    stream.write(value_str.data(), value_str.size());
    stream.put(seperator);
    
    return !stream.bad();
}

bool charta::pdf::PDFWriter::writeComment(std::ostream &stream, std::string_view comment)
{
    stream.put(PDF_COMMENT_PREFIX);
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
    stream.write(PDF_NEWLINE, 2);
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

charta::pdf::PDFWriter::ObjectWriteInformation &charta::pdf::PDFWriter::startWriteObject(std::ostream &stream)
{
    auto &obj = allocateWriteObject();
    obj.write_pos = stream.tellp();
    obj.written = true;

    writeInteger(stream, obj.id);
    writeInteger(stream, 0);
    writeKeyword(stream, PDF_KEYWORD_OBJECT);

    return obj;
}

bool charta::pdf::PDFWriter::endWriteObject(std::ostream &stream)
{
    return writeKeyword(stream, PDF_KEYWORD_END_OBJECT);
}

charta::pdf::PDFWriter::ObjectWriteInformation &charta::pdf::PDFWriter::allocateWriteObject()
{
    auto &obj = m_writeObjects.emplace_back();
    obj.id = m_writeObjects.size();
    return obj;
}