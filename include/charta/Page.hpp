#pragma once
#include "Content.hpp"
#include "PagePresets.hpp"

namespace charta::pdf
{
class Page
{
  private:
    Rectangleu m_mediaBox;
    std::vector<Content> m_contents;

  public:
    Page(const Rectangleu &mediaBox = presets::A4Paper_Portrait) : m_mediaBox(mediaBox)
    {
    }

    const Rectangleu &getMediaBox() const
    {
        return m_mediaBox;
    }
};
} // namespace charta::pdf