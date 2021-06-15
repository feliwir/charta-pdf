#pragma once
#include <optional>
#include <string_view>
#include <vector>

#include "Info.hpp"
#include "Page.hpp"
#include "Vector2.hpp"

namespace charta::pdf
{
using PDFVersion = Vector2u;
class Document
{
  private:
    PDFVersion m_version;
    std::optional<Info> m_info;
    std::vector<Page> m_pages;

  public:
    Document(PDFVersion version = {1, 3}) : m_version(version)
    {
    }

    inline void setInfo(const Info &info)
    {
        m_info = info;
    }

    inline std::optional<Info> getInfo() const
    {
        return m_info;
    }

    inline const std::vector<Page> getPages() const
    {
        return m_pages;
    }

    inline void addPage(const Page &page)
    {
        m_pages.emplace_back(page);
    }

    bool saveToStream(std::ostream &stream);
    bool saveToFile(std::string_view filepath);

    inline const PDFVersion &getVersion() const
    {
        return m_version;
    }
};
} // namespace charta::pdf