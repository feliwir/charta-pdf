#pragma once
#include <charta/Document.hpp>
#include <map>
#include <ostream>
#include <string_view>
#include <variant>
#include <vector>

#include "ObjectWriteInfo.hpp"
#include "Trailer.hpp"
#include "LiteralString.hpp"

namespace charta::pdf
{
using DictValue = std::variant<std::string, int, ObjectReference, LiteralString>;
class Writer
{
  private:
    std::vector<ObjectWriteInformation> m_writeObjects;
    size_t m_indentLevel = 0;
    Trailer m_trailer;

  public:
    // Header & EOF
    bool writeHeader(std::ostream &ostream, const Document &doc);
    bool writeEndOfFile(std::ostream &ostream);

    // XRef
    bool writeXRefTable(std::ostream &ostream, const Document &doc, size_t &tablePos);
    bool writeXRefTableReference(std::ostream &ostream, const size_t tablePos);

    // Trailer
    bool writeTrailer(std::ostream &ostream);

    bool writeCatalogObject(std::ostream &ostream);
    bool writeInfoObject(std::ostream &ostream, const Info& info);

  private:
    // Primitive writes
    bool writeInteger(std::ostream &ostream, int value, char seperator = ' ');
    bool writeLiteralString(std::ostream &ostream, const LiteralString& value, char seperator = ' ');
    bool writeComment(std::ostream &ostream, std::string_view comment);
    bool writeKeyword(std::ostream &ostream, std::string_view keyword);
    bool writeNewLine(std::ostream &ostream);
    bool writeDictionary(std::ostream &ostream, const std::map<std::string, DictValue> &dict);
    bool writeKey(std::ostream &ostream, std::string_view key);
    bool writeValue(std::ostream &ostream, const DictValue &value);
    bool writeIndent(std::ostream &ostream);
    bool writeName(std::ostream &ostream, std::string_view name, char seperator = ' ');
    bool writeIndirectObject(std::ostream &ostream, ObjectReference ref);
    bool writeSeperator(std::ostream &stream, char seperator = ' ');

    ObjectWriteInformation &allocateWriteObject();
    ObjectWriteInformation &startWriteObject(std::ostream &stream);
    bool endWriteObject(std::ostream &stream);
};
} // namespace charta::pdf