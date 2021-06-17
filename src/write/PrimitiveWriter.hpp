#pragma once
#include "../Literals.hpp"
#include <ostream>
#include <string_view>

namespace charta::pdf
{
class PrimitiveWriter
{
  private:
    size_t m_indentLevel = 0;

  public:
    bool writeComment(std::ostream &ostream, std::string_view comment);
    bool writeKeyword(std::ostream &ostream, std::string_view keyword);
    bool writeNewLine(std::ostream &ostream);
    bool writeIndent(std::ostream &ostream);
    bool writeSeperator(std::ostream &stream, char seperator = PDF_SPACE);
    inline size_t &getIndentLevel()
    {
        return m_indentLevel;
    }
};
} // namespace charta::pdf