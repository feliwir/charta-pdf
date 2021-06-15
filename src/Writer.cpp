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

    if (!writeInteger(stream, tablePos, '\0'))
    {
        return false;
    }

    return writeNewLine(stream);
}

bool charta::pdf::Writer::writePageTree(std::ostream &stream, const Document &doc)
{
    // No reference here, since it will be invalidated later
    auto pageTree = allocateWriteObject();

    // Write pages
    std::vector<ObjectWriteInformation> writtenPages;
    for (const auto &page : doc.getPages())
    {
        writtenPages.emplace_back(startWriteObject(stream));

        Array mediaBoxArr({static_cast<IntegerObject>(page.getMediaBox().getLower().x()),
                           static_cast<IntegerObject>(page.getMediaBox().getLower().y()),
                           static_cast<IntegerObject>(page.getMediaBox().getUpper().x()),
                           static_cast<IntegerObject>(page.getMediaBox().getUpper().y())});

        Dictionary catalogDict;
        catalogDict[PDF_DICT_KEY_TYPE] = PDF_DICT_VALUE_TYPE_PAGE;
        catalogDict[PDF_DICT_KEY_PARENT] = pageTree.id;
        catalogDict[PDF_DICT_KEY_MEDIABOX] = mediaBoxArr;

        if (!writeDictionary(stream, catalogDict))
        {
            return false;
        }

        if (!endWriteObject(stream))
        {
            return false;
        }
    }

    // Write pages tree
    auto &pageTreeRef = m_writeObjects[pageTree.id - 1];

    startWriteObject(stream, pageTreeRef);

    Array pagesArr;
    for (auto &page : writtenPages)
    {
        pagesArr.emplace_back() = page.id;
    }

    Dictionary catalogDict;
    catalogDict[PDF_DICT_KEY_TYPE] = PDF_DICT_VALUE_TYPE_PAGES;
    catalogDict[PDF_DICT_KEY_COUNT] = static_cast<IntegerObject>(writtenPages.size());
    catalogDict[PDF_DICT_KEY_KIDS] = pagesArr;

    if (!writeDictionary(stream, catalogDict))
    {
        return false;
    }

    m_catalog.setPages(pageTree.id);

    return endWriteObject(stream);
}

bool charta::pdf::Writer::writeCatalogObject(std::ostream &stream)
{
    auto &object = startWriteObject(stream);
    m_trailer.setRoot(object.id);

    Dictionary catalogDict;
    catalogDict[PDF_DICT_KEY_TYPE] = PDF_DICT_VALUE_TYPE_CATALOG;

    if (m_catalog.getPages().has_value())
    {
        catalogDict[PDF_DICT_VALUE_TYPE_PAGES] = m_catalog.getPages().value();
    }

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

    Dictionary catalogDict;
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

    Dictionary trailerDict;
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

bool charta::pdf::Writer::writeArray(std::ostream &stream, const Array &arr)
{
    stream.put(PDF_LEFT_SQUARE_BRACKET);

    for (size_t i = 0; i < arr.size(); i++)
    {
        const auto &obj = arr[i];
        if (!writeObject(stream, obj))
            return false;
        // The last element doesn't need a seperator
        if (i < (arr.size() - 1) && !writeSeperator(stream))
            return false;
    }

    stream.put(PDF_RIGHT_SQUARE_BRACKET);

    return !stream.bad();
}

bool charta::pdf::Writer::writeDictionary(std::ostream &stream, const Dictionary &dict)
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
        if (!writeIndent(stream))
        {
            return false;
        }
        if (!writeObject(stream, keyValue.first))
        {
            return false;
        }
        if (!writeSeperator(stream))
        {
            return false;
        }
        if (!writeObject(stream, keyValue.second))
        {
            return false;
        }
        if (!writeNewLine(stream))
        {
            return false;
        }
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

bool charta::pdf::Writer::writeSeperator(std::ostream &stream, char seperator)
{
    if (seperator)
        stream.put(seperator);
    return !stream.bad();
}

bool charta::pdf::Writer::writeObject(std::ostream &stream, const Object &value)
{
    if (std::holds_alternative<IntegerObject>(value))
    {
        if (!writeInteger(stream, std::get<IntegerObject>(value), '\0'))
            return false;
    }
    else if (std::holds_alternative<IndirectObject>(value))
    {
        if (!writeIndirectObject(stream, std::get<IndirectObject>(value)))
            return false;
    }
    else if (std::holds_alternative<LiteralString>(value))
    {
        if (!writeLiteralString(stream, std::get<LiteralString>(value), '\0'))
            return false;
    }
    else if (std::holds_alternative<Array>(value))
    {
        if (!writeArray(stream, std::get<Array>(value)))
            return false;
    }
    else if (std::holds_alternative<Dictionary>(value))
    {
        if (!writeDictionary(stream, std::get<Dictionary>(value)))
            return false;
    }
    else if (std::holds_alternative<NameObject>(value))
    {
        if (!writeName(stream, std::get<NameObject>(value), '\0'))
            return false;
    }
    else
    {
        return false;
    }

    return true;
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
    return startWriteObject(stream, allocateWriteObject());
}

charta::pdf::ObjectWriteInformation &charta::pdf::Writer::startWriteObject(std::ostream &stream,
                                                                           ObjectWriteInformation &writeInfo)
{
    writeInfo.write_pos = stream.tellp();
    writeInfo.written = true;

    writeInteger(stream, writeInfo.id);
    writeInteger(stream, 0);
    writeKeyword(stream, PDF_KEYWORD_OBJECT);

    return writeInfo;
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