#pragma once
#include "Vector2.hpp"
#include <string_view>

namespace charta::pdf
{
using PDFVersion = Vector2u;
class PDFDocument
{
  private:
    PDFVersion m_version;

  public:
    PDFDocument(PDFVersion version = {1, 3}) : m_version(version)
    {
    }

    bool saveTo(std::string_view filepath);

    inline const PDFVersion &getVersion() const
    {
        return m_version;
    }
};
} // namespace charta::pdf