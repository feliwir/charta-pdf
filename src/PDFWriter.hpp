#pragma once
#include <charta/PDFDocument.hpp>
#include <map>
#include <ostream>
#include <string_view>
#include <vector>

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
    
    bool writeCatalogObject(std::ostream &ostream);

  private:
    // Primitive writes
    bool writeInteger(std::ostream &ostream, int value, char seperator = ' ');
    bool writeComment(std::ostream &ostream, std::string_view comment);
    bool writeKeyword(std::ostream &ostream, std::string_view keyword);
    bool writeNewLine(std::ostream &ostream);
    bool writeDictionary(std::ostream &ostream, const std::map<std::string, std::string> &dict);

    struct ObjectWriteInformation
    {
        bool written = false;
        size_t write_pos;
        size_t id;
    };

    ObjectWriteInformation &allocateWriteObject();
    ObjectWriteInformation &startWriteObject(std::ostream &stream);
    bool endWriteObject(std::ostream &stream);

    std::vector<ObjectWriteInformation> m_writeObjects;
};
} // namespace charta::pdf