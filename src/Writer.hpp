#pragma once
#include <charta/Document.hpp>
#include <ostream>
#include <string_view>
#include <vector>

#include "Catalog.hpp"
#include "Literals.hpp"
#include "Trailer.hpp"
#include "write/ObjectWriter.hpp"
#include "write/PrimitiveWriter.hpp"

namespace charta::pdf
{

class Writer
{
  private:
    PrimitiveWriter m_primWriter;
    ObjectWriter m_objWriter;

    Trailer m_trailer;
    Catalog m_catalog;

  public:
    Writer();

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
};
} // namespace charta::pdf