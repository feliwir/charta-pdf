#include "Writer.hpp"
#include <iomanip>
#include <sstream>

charta::pdf::Writer::Writer() : m_objWriter(m_primWriter)
{
    auto &headObj = m_objWriter.allocateWriteObject();
    headObj.generation = std::numeric_limits<uint16_t>::max();
}

bool charta::pdf::Writer::writeHeader(std::ostream &stream, const Document &doc)
{
    // Write a comment containing the PDF version
    const std::string version_comment = "PDF-" + doc.getVersion().toString();
    if (!m_primWriter.writeComment(stream, version_comment))
    {
        return false;
    }

    // Indicates that this PDF contains binary data
    const std::string binary_comment = "\xbd\xbe\xbc";
    if (!m_primWriter.writeComment(stream, binary_comment))
    {
        return false;
    }

    return true;
}

bool charta::pdf::Writer::writeEndOfFile(std::ostream &stream)
{
    // Indicates that this PDF ends
    if (!m_primWriter.writeComment(stream, PDF_COMMENT_EOF))
    {
        return false;
    }

    return true;
}

bool charta::pdf::Writer::writeXRefTable(std::ostream &stream, const Document &doc, size_t &tablePos)
{
    tablePos = stream.tellp();

    if (!m_primWriter.writeKeyword(stream, PDF_KEYWORD_XREF))
    {
        return false;
    }

    if (!m_objWriter.writeInteger(stream, 0))
    {
        return false;
    }

    if (!m_objWriter.writeInteger(stream, m_objWriter.getObjects().size(), '\0'))
    {
        return false;
    }

    if (!m_primWriter.writeNewLine(stream))
    {
        return false;
    }

    for (const auto &writeObj : m_objWriter.getObjects())
    {
        // Object stream position
        std::stringstream ss;
        ss << std::setw(10) << std::setfill('0') << writeObj.write_pos;
        stream << ss.rdbuf();

        stream.put(PDF_SPACE);

        // Generation number
        ss.clear();
        ss << std::setw(5) << std::setfill('0') << writeObj.generation;
        stream << ss.rdbuf();

        // Free or used
        stream.put(PDF_SPACE);
        stream.put(writeObj.written ? 'n' : 'f');
        m_primWriter.writeNewLine(stream);
    }

    return !stream.bad();
}

bool charta::pdf::Writer::writeXRefTableReference(std::ostream &stream, const size_t tablePos)
{
    if (!m_primWriter.writeKeyword(stream, PDF_KEYWORD_STARTXREF))
    {
        return false;
    }

    if (!m_objWriter.writeInteger(stream, tablePos, '\0'))
    {
        return false;
    }

    return m_primWriter.writeNewLine(stream);
}

bool charta::pdf::Writer::writePageTree(std::ostream &stream, const Document &doc)
{
    // No reference here, since it will be invalidated later
    auto pageTree = m_objWriter.allocateWriteObject();

    // Write pages
    std::vector<ObjectWriteInformation> writtenPages;
    for (const auto &page : doc.getPages())
    {
        writtenPages.emplace_back(m_objWriter.startWriteObject(stream));

        Array mediaBoxArr({static_cast<IntegerObject>(page.getMediaBox().getLower().x()),
                           static_cast<IntegerObject>(page.getMediaBox().getLower().y()),
                           static_cast<IntegerObject>(page.getMediaBox().getUpper().x()),
                           static_cast<IntegerObject>(page.getMediaBox().getUpper().y())});

        Dictionary catalogDict;
        catalogDict[PDF_DICT_KEY_TYPE] = PDF_DICT_VALUE_TYPE_PAGE;
        catalogDict[PDF_DICT_KEY_PARENT] = pageTree.id;
        catalogDict[PDF_DICT_KEY_MEDIABOX] = mediaBoxArr;

        if (!m_objWriter.writeDictionary(stream, catalogDict))
        {
            return false;
        }

        if (!m_objWriter.endWriteObject(stream))
        {
            return false;
        }
    }

    // Write pages tree
    auto &pageTreeRef = m_objWriter.getObjects()[pageTree.id];

    m_objWriter.startWriteObject(stream, pageTreeRef);

    Array pagesArr;
    for (auto &page : writtenPages)
    {
        pagesArr.emplace_back() = page.id;
    }

    Dictionary catalogDict;
    catalogDict[PDF_DICT_KEY_TYPE] = PDF_DICT_VALUE_TYPE_PAGES;
    catalogDict[PDF_DICT_KEY_COUNT] = static_cast<IntegerObject>(writtenPages.size());
    catalogDict[PDF_DICT_KEY_KIDS] = pagesArr;

    if (!m_objWriter.writeDictionary(stream, catalogDict))
    {
        return false;
    }

    m_catalog.setPages(pageTree.id);

    return m_objWriter.endWriteObject(stream);
}

bool charta::pdf::Writer::writeCatalogObject(std::ostream &stream)
{
    auto &object = m_objWriter.startWriteObject(stream);
    m_trailer.setRoot(object.id);

    Dictionary catalogDict;
    catalogDict[PDF_DICT_KEY_TYPE] = PDF_DICT_VALUE_TYPE_CATALOG;

    if (m_catalog.getPages().has_value())
    {
        catalogDict[PDF_DICT_VALUE_TYPE_PAGES] = m_catalog.getPages().value();
    }

    if (!m_objWriter.writeDictionary(stream, catalogDict))
    {
        return false;
    }

    return m_objWriter.endWriteObject(stream);
}

bool charta::pdf::Writer::writeInfoObject(std::ostream &stream, const Info &info)
{
    auto &object = m_objWriter.startWriteObject(stream);
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

    if (!m_objWriter.writeDictionary(stream, catalogDict))
    {
        return false;
    }

    return m_objWriter.endWriteObject(stream);
}

bool charta::pdf::Writer::writeTrailer(std::ostream &stream)
{
    if (!m_primWriter.writeKeyword(stream, PDF_KEYWORD_TRAILER))
    {
        return false;
    }

    Dictionary trailerDict;
    trailerDict[PDF_DICT_KEY_SIZE] = static_cast<IntegerObject>(m_objWriter.getObjects().size());
    trailerDict[PDF_DICT_KEY_ROOT] = m_trailer.getRoot();
    if (m_trailer.getInfo().has_value())
        trailerDict[PDF_DICT_KEY_INFO] = m_trailer.getInfo().value();

    if (!m_objWriter.writeDictionary(stream, trailerDict))
    {
        return false;
    }

    return true;
}
