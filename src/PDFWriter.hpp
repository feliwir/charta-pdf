#pragma once
#include <charta/PDFDocument.hpp>
#include <map>
#include <ostream>
#include <string_view>

namespace charta::pdf
{
class PDFWriter
{
  public:
    // Header & EOF
    bool writeHeader(std::ostream &ostream, const PDFDocument &doc);
    bool writeEndOfFile(std::ostream &ostream);

    // XRef
    bool writeXRefTable(std::ostream &ostream, const PDFDocument &doc, size_t &tablePos);
    bool writeXRefTableReference(std::ostream &ostream, const size_t tablePos);

    // Trailer
    bool writeTrailer(std::ostream &ostream, const PDFDocument &doc);

    // Primitive writes
    bool writeInteger(std::ostream &ostream, int value);
    bool writeComment(std::ostream &ostream, std::string_view comment);
    bool writeKeyword(std::ostream &ostream, std::string_view keyword);
    bool writeNewLine(std::ostream &ostream);
    bool writeDictionary(std::ostream &ostream, const std::map<std::string, std::string>& dict);
};
} // namespace charta::pdf