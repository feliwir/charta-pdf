#pragma once
#include "Rectangle.hpp"

namespace charta::pdf
{
class Page
{
  private:
    Rectangleu m_mediaBox;

  public:
    Page(const Rectangleu &mediaBox = {{0u, 0u}, {600u, 600u}}) : m_mediaBox(mediaBox)
    {
    }
};
} // namespace charta::pdf