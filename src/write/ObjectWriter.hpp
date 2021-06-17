#pragma once
#include "../Literals.hpp"
#include "../objects/Array.hpp"
#include "../objects/Dictionary.hpp"
#include "../objects/IndirectObject.hpp"
#include "../objects/LiteralString.hpp"
#include "ObjectWriteInfo.hpp"
#include "PrimitiveWriter.hpp"

namespace charta::pdf
{
class ObjectWriter
{
  private:
    std::vector<ObjectWriteInformation> m_writeObjects;
    PrimitiveWriter &m_writer;

  public:
    inline ObjectWriter(PrimitiveWriter &writer) : m_writer(writer)
    {
    }

    bool writeInteger(std::ostream &ostream, int value, char seperator = PDF_SPACE);
    bool writeLiteralString(std::ostream &ostream, const LiteralString &value, char seperator = PDF_SPACE);
    bool writeArray(std::ostream &ostream, const Array &arr);
    bool writeDictionary(std::ostream &ostream, const Dictionary &dict);
    bool writeName(std::ostream &ostream, std::string_view name, char seperator = PDF_SPACE);
    bool writeIndirectObject(std::ostream &ostream, IndirectObject ref);
    bool writeObject(std::ostream &ostream, const Object &value);

    ObjectWriteInformation &allocateWriteObject();
    ObjectWriteInformation &startWriteObject(std::ostream &stream);
    ObjectWriteInformation &startWriteObject(std::ostream &stream, ObjectWriteInformation &writeInformation);
    bool endWriteObject(std::ostream &stream);

    inline const std::vector<ObjectWriteInformation> &getObjects()
    {
        return m_writeObjects;
    }
};
} // namespace charta::pdf