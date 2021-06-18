#pragma once
#include <optional>
#include <string_view>
#include <vector>

#include "Font.hpp"
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
    std::vector<Font> m_fonts;

  public:
    Document(PDFVersion version = {1, 3}) : m_version(version)
    {
    }

    inline const PDFVersion &getVersion() const
    {
        return m_version;
    }

    inline void setInfo(const Info &info)
    {
        m_info = info;
    }

    inline std::optional<Info> getInfo() const
    {
        return m_info;
    }

    // Fonts
    bool addFontFromStream(std::istream &stream, bool embed = true);
    bool addFontFromFile(std::string_view filepath, bool embed = true);

    // Pages
    inline const std::vector<Page> getPages() const
    {
        return m_pages;
    }

    inline void addPage(const Page &page)
    {
        m_pages.emplace_back(page);
    }

    // Saving
    bool saveToStream(std::ostream &stream);
    bool saveToFile(std::string_view filepath);
};
} // namespace charta::pdf