#include "Writer.hpp"
#include <iomanip>
#include <sstream>

bool charta::pdf::Writer::writeHeader(std::ostream &stream, const Document &doc)
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

bool charta::pdf::Writer::writeEndOfFile(std::ostream &stream)
{
    // Indicates that this PDF ends
    if (!writeComment(stream, PDF_COMMENT_EOF))
    {
        return false;
    }

    return true;
}

bool charta::pdf::Writer::writeXRefTable(std::ostream &stream, const Document &doc, size_t &tablePos)
{
    tablePos = stream.tellp();

    if (!writeKeyword(stream, PDF_KEYWORD_XREF))
    {
        return false;
    }

    for (const auto &writeObj : m_writeObjects)
    {
        // write obj position
        std::stringstream ss;
        ss << std::setw(10) << std::setfill('0') << writeObj.write_pos;
        stream << ss.rdbuf();

        stream.put(PDF_SPACE);

        ss.clear();
        ss << std::setw(5) << std::setfill('0') << 0;
        stream << ss.rdbuf();

        stream.put(PDF_SPACE);
        stream.put('n');
        writeNewLine(stream);
    }

    return !stream.bad();
}

bool charta::pdf::Writer::writeXRefTableReference(std::ostream &stream, const size_t tablePos)
{
    if (!writeKeyword(stream, PDF_KEYWORD_STARTXREF))
    {
        return false;
    }

    if (!writeInteger(stream, tablePos,'\0'))
    {
        return false;
    }

    return writeNewLine(stream);
}

bool charta::pdf::Writer::writeCatalogObject(std::ostream &stream)
{
    auto &object = startWriteObject(stream);
    m_trailer.setRoot(object.id);

    std::map<std::string, DictValue> catalogDict;
    catalogDict[PDF_DICT_KEY_TYPE] = PDF_DICT_VALUE_CATALOG;

    if (!writeDictionary(stream, catalogDict))
    {
        return false;
    }

    return endWriteObject(stream);
}

bool charta::pdf::Writer::writeInfoObject(std::ostream &stream, const Info &info)
{
    auto &object = startWriteObject(stream);
    m_trailer.setInfo(object.id);

    std::map<std::string, DictValue> catalogDict;
    if (!info.Title.empty())
        catalogDict[PDF_DICT_KEY_INFO_TITLE] = LiteralString(info.Title);
    if (!info.Author.empty())
        catalogDict[PDF_DICT_KEY_INFO_AUTHOR] = LiteralString(info.Author);
    if (!info.Subject.empty())
        catalogDict[PDF_DICT_KEY_INFO_SUBJECT] = LiteralString(info.Subject);
    if (!info.Keywords.empty())
        catalogDict[PDF_DICT_KEY_INFO_KEYWORDS] = LiteralString(info.Keywords);

    if (!writeDictionary(stream, catalogDict))
    {
        return false;
    }

    return endWriteObject(stream);
}

bool charta::pdf::Writer::writeTrailer(std::ostream &stream)
{
    if (!writeKeyword(stream, PDF_KEYWORD_TRAILER))
    {
        return false;
    }

    std::map<std::string, DictValue> trailerDict;
    trailerDict[PDF_DICT_KEY_SIZE] = 0;
    trailerDict[PDF_DICT_KEY_ROOT] = m_trailer.getRoot();
    if (m_trailer.getInfo().has_value())
        trailerDict[PDF_DICT_KEY_INFO] = m_trailer.getInfo().value();

    if (!writeDictionary(stream, trailerDict))
    {
        return false;
    }

    return true;
}

bool charta::pdf::Writer::writeInteger(std::ostream &stream, int value, char seperator)
{
    std::string value_str = std::to_string(value);
    stream.write(value_str.data(), value_str.size());

    return writeSeperator(stream, seperator);
}

bool charta::pdf::Writer::writeLiteralString(std::ostream &stream, const LiteralString &value, char seperator)
{
    stream.put(PDF_LEFT_PARENTHESIS);
    stream.write(value.getContent().data(), value.getContent().size());
    stream.put(PDF_RIGHT_PARENTHESIS);

    return writeSeperator(stream, seperator);
}

bool charta::pdf::Writer::writeComment(std::ostream &stream, std::string_view comment)
{
    stream.put(PDF_PERCENT_SIGN);
    stream.write(comment.data(), comment.size());

    return writeNewLine(stream);
}

bool charta::pdf::Writer::writeKeyword(std::ostream &stream, std::string_view keyword)
{
    stream.write(keyword.data(), keyword.size());

    return writeNewLine(stream);
}

bool charta::pdf::Writer::writeNewLine(std::ostream &stream)
{
    stream.write(PDF_EOL, sizeof(PDF_EOL));
    return !stream.bad();
}

bool charta::pdf::Writer::writeDictionary(std::ostream &stream, const std::map<std::string, DictValue> &dict)
{
    if (!writeIndent(stream))
    {
        return false;
    }

    if (!writeKeyword(stream, PDF_DICT_START))
    {
        return false;
    }

    m_indentLevel++;

    for (const auto &keyValue : dict)
    {
        writeKey(stream, keyValue.first);
        writeValue(stream, keyValue.second);
    }

    m_indentLevel--;

    if (!writeIndent(stream))
    {
        return false;
    }

    return writeKeyword(stream, PDF_DICT_END);
}

bool charta::pdf::Writer::writeName(std::ostream &stream, std::string_view name, char seperator)
{
    stream.put(PDF_SOLIDUS);

    // TODO: Escape ASCII 0-32
    stream.write(name.data(), name.size());

    return writeSeperator(stream, seperator);
}

bool charta::pdf::Writer::writeKey(std::ostream &stream, std::string_view key)
{
    if (!writeIndent(stream))
    {
        return false;
    }

    return writeName(stream, key, '\0');
}

bool charta::pdf::Writer::writeSeperator(std::ostream &stream, char seperator)
{
    if (seperator)
        stream.put(seperator);
    return !stream.bad();
}

bool charta::pdf::Writer::writeValue(std::ostream &stream, const DictValue &value)
{
    if (std::holds_alternative<int>(value))
    {
        if (!writeSeperator(stream))
            return false;
        if (!writeInteger(stream, std::get<int>(value), '\0'))
            return false;
    }
    else if (std::holds_alternative<IndirectObject>(value))
    {
        if (!writeSeperator(stream))
            return false;
        if (!writeIndirectObject(stream, std::get<IndirectObject>(value)))
            return false;
    }
    else if (std::holds_alternative<LiteralString>(value))
    {
        if (!writeLiteralString(stream, std::get<LiteralString>(value),'\0'))
            return false;
    }
    else
    {
        if (!writeSeperator(stream))
            return false;
        if (!writeName(stream, std::get<NameObject>(value), '\0'))
            return false;
    }

    return writeNewLine(stream);
}

bool charta::pdf::Writer::writeIndirectObject(std::ostream &stream, IndirectObject ref)
{
    if (!writeInteger(stream, ref))
    {
        return false;
    }

    if (!writeInteger(stream, 0))
    {
        return false;
    }

    stream.put(PDF_REFERENCE_SUFFIX);

    return !stream.bad();
}

bool charta::pdf::Writer::writeIndent(std::ostream &stream)
{
    for (size_t l = 0; l < m_indentLevel; l++)
    {
        stream.put(PDF_HORIZONTAL_TAB);
    }

    return !stream.bad();
}

charta::pdf::ObjectWriteInformation &charta::pdf::Writer::startWriteObject(std::ostream &stream)
{
    auto &obj = allocateWriteObject();
    obj.write_pos = stream.tellp();
    obj.written = true;

    writeInteger(stream, obj.id);
    writeInteger(stream, 0);
    writeKeyword(stream, PDF_KEYWORD_OBJECT);

    return obj;
}

bool charta::pdf::Writer::endWriteObject(std::ostream &stream)
{
    return writeKeyword(stream, PDF_KEYWORD_END_OBJECT);
}

charta::pdf::ObjectWriteInformation &charta::pdf::Writer::allocateWriteObject()
{
    auto &obj = m_writeObjects.emplace_back();
    obj.id = m_writeObjects.size();
    return obj;
}