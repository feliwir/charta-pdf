#pragma once
#include <string>
#include <string_view>

namespace charta::pdf
{
class LiteralString
{
  private:
    std::string m_content;

  public:
    LiteralString(std::string_view content)
    {
        m_content = content;
    }

    // TODO: escape the string
    inline std::string_view getContent() const
    {
        return m_content;
    }
};
} // namespace charta::pdf