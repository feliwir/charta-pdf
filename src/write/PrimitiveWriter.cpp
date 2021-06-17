#include "PrimitiveWriter.hpp"

bool charta::pdf::PrimitiveWriter::writeComment(std::ostream &stream, std::string_view comment)
{
    stream.put(PDF_PERCENT_SIGN);
    stream.write(comment.data(), comment.size());

    return writeNewLine(stream);
}

bool charta::pdf::PrimitiveWriter::writeKeyword(std::ostream &stream, std::string_view keyword)
{
    stream.write(keyword.data(), keyword.size());

    return writeNewLine(stream);
}

bool charta::pdf::PrimitiveWriter::writeNewLine(std::ostream &stream)
{
    stream.write(PDF_EOL, sizeof(PDF_EOL));
    return !stream.bad();
}

bool charta::pdf::PrimitiveWriter::writeSeperator(std::ostream &stream, char seperator)
{
    if (seperator)
        stream.put(seperator);
    return !stream.bad();
}

bool charta::pdf::PrimitiveWriter::writeIndent(std::ostream &stream)
{
    for (size_t l = 0; l < m_indentLevel; l++)
    {
        stream.put(PDF_HORIZONTAL_TAB);
    }

    return !stream.bad();
}