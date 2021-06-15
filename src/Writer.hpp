#pragma once
#include <charta/Document.hpp>
#include <ostream>
#include <string_view>
#include <vector>

#include "Catalog.hpp"
#include "Literals.hpp"
#include "ObjectWriteInfo.hpp"
#include "Trailer.hpp"
#include "objects/Array.hpp"
#include "objects/Dictionary.hpp"
#include "objects/IndirectObject.hpp"
#include "objects/LiteralString.hpp"

namespace charta::pdf
{

class Writer
{
  private:
    std::vector<ObjectWriteInformation> m_writeObjects;
    size_t m_indentLevel = 0;
    Trailer m_trailer;
    Catalog m_catalog;

  public:
    // Header & EOF
    bool writeHeader(std::ostream &ostream, const Document &doc);
    bool writeEndOfFile(std::ostream &ostream);

    // XRef
    bool writeXRefTable(std::ostream &ostream, const Document &doc, size_t &tablePos);
    bool writeXRefTableReference(std::ostream &ostream, const size_t tablePos);

    // Trailer
    bool writeTrailer(std::ostream &ostream);

    bool writePageTree(std::ostream &ostream, const Document &doc);
    bool writeCatalogObject(std::ostream &ostream);
    bool writeInfoObject(std::ostream &ostream, const Info &info);

  private:
    // Primitive writes
    bool writeInteger(std::ostream &ostream, int value, char seperator = PDF_SPACE);
    bool writeLiteralString(std::ostream &ostream, const LiteralString &value, char seperator = PDF_SPACE);
    bool writeComment(std::ostream &ostream, std::string_view comment);
    bool writeKeyword(std::ostream &ostream, std::string_view keyword);
    bool writeNewLine(std::ostream &ostream);
    bool writeArray(std::ostream &ostream, const Array &arr);
    bool writeDictionary(std::ostream &ostream, const Dictionary &dict);
    bool writeIndent(std::ostream &ostream);
    bool writeName(std::ostream &ostream, std::string_view name, char seperator = PDF_SPACE);
    bool writeIndirectObject(std::ostream &ostream, IndirectObject ref);
    bool writeSeperator(std::ostream &stream, char seperator = PDF_SPACE);

    // Object write
    bool writeObject(std::ostream &ostream, const Object &value);

    ObjectWriteInformation &allocateWriteObject();
    ObjectWriteInformation &startWriteObject(std::ostream &stream);
    ObjectWriteInformation &startWriteObject(std::ostream &stream, ObjectWriteInformation &writeInformation);
    bool endWriteObject(std::ostream &stream);
};
} // namespace charta::pdf