#pragma once
#include <optional>
#include <string_view>

#include "Info.hpp"
#include "Vector2.hpp"

namespace charta::pdf
{
using PDFVersion = Vector2u;
class Document
{
  private:
    PDFVersion m_version;
    std::optional<Info> m_info;

  public:
    Document(PDFVersion version = {1, 3}) : m_version(version)
    {
    }

    inline void setInfo(const Info &info)
    {
        m_info = info;
    }

    inline std::optional<Info> getInfo()
    {
        return m_info;
    }

    bool saveToStream(std::ostream &stream);
    bool saveToFile(std::string_view filepath);

    inline const PDFVersion &getVersion() const
    {
        return m_version;
    }
};
} // namespace charta::pdf