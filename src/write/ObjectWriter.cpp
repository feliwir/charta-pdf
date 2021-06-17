#include "ObjectWriter.hpp"

bool charta::pdf::ObjectWriter::writeDictionary(std::ostream &stream, const Dictionary &dict)
{
    if (!m_writer.writeIndent(stream))
    {
        return false;
    }

    if (!m_writer.writeKeyword(stream, PDF_DICT_START))
    {
        return false;
    }

    m_writer.getIndentLevel()++;

    for (const auto &keyValue : dict)
    {
        if (!m_writer.writeIndent(stream))
        {
            return false;
        }
        if (!writeObject(stream, keyValue.first))
        {
            return false;
        }
        if (!m_writer.writeSeperator(stream))
        {
            return false;
        }
        if (!writeObject(stream, keyValue.second))
        {
            return false;
        }
        if (!m_writer.writeNewLine(stream))
        {
            return false;
        }
    }

    m_writer.getIndentLevel()--;

    if (!m_writer.writeIndent(stream))
    {
        return false;
    }

    return m_writer.writeKeyword(stream, PDF_DICT_END);
}

bool charta::pdf::ObjectWriter::writeName(std::ostream &stream, std::string_view name, char seperator)
{
    stream.put(PDF_SOLIDUS);

    // TODO: Escape ASCII 0-32
    stream.write(name.data(), name.size());

    return m_writer.writeSeperator(stream, seperator);
}

bool charta::pdf::ObjectWriter::writeObject(std::ostream &stream, const Object &value)
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

bool charta::pdf::ObjectWriter::writeIndirectObject(std::ostream &stream, IndirectObject ref)
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

charta::pdf::ObjectWriteInformation &charta::pdf::ObjectWriter::startWriteObject(std::ostream &stream)
{
    return startWriteObject(stream, allocateWriteObject());
}

charta::pdf::ObjectWriteInformation &charta::pdf::ObjectWriter::startWriteObject(std::ostream &stream,
                                                                                 ObjectWriteInformation &writeInfo)
{
    writeInfo.write_pos = stream.tellp();
    writeInfo.written = true;

    writeInteger(stream, writeInfo.id);
    writeInteger(stream, 0);
    m_writer.writeKeyword(stream, PDF_KEYWORD_OBJECT);

    return writeInfo;
}

bool charta::pdf::ObjectWriter::endWriteObject(std::ostream &stream)
{
    return m_writer.writeKeyword(stream, PDF_KEYWORD_END_OBJECT);
}

charta::pdf::ObjectWriteInformation &charta::pdf::ObjectWriter::allocateWriteObject()
{
    auto &obj = m_writeObjects.emplace_back();
    obj.id = m_writeObjects.size() - 1;
    return obj;
}

bool charta::pdf::ObjectWriter::writeInteger(std::ostream &stream, int value, char seperator)
{
    std::string value_str = std::to_string(value);
    stream.write(value_str.data(), value_str.size());

    return m_writer.writeSeperator(stream, seperator);
}

bool charta::pdf::ObjectWriter::writeLiteralString(std::ostream &stream, const LiteralString &value, char seperator)
{
    stream.put(PDF_LEFT_PARENTHESIS);
    stream.write(value.getContent().data(), value.getContent().size());
    stream.put(PDF_RIGHT_PARENTHESIS);

    return m_writer.writeSeperator(stream, seperator);
}

bool charta::pdf::ObjectWriter::writeArray(std::ostream &stream, const Array &arr)
{
    stream.put(PDF_LEFT_SQUARE_BRACKET);

    for (size_t i = 0; i < arr.size(); i++)
    {
        const auto &obj = arr[i];
        if (!writeObject(stream, obj))
            return false;
        // The last element doesn't need a seperator
        if (i < (arr.size() - 1) && !m_writer.writeSeperator(stream))
            return false;
    }

    stream.put(PDF_RIGHT_SQUARE_BRACKET);

    return !stream.bad();
}