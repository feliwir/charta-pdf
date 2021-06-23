#pragma once
#include "../objects/Array.hpp"
#include <charta/Rectangle.hpp>

namespace charta::pdf
{
class WriteHelper
{
  public:
    template <class ObjType, class T> static inline Array rectToArray(const Rectangle<T> &rect)
    {
        return Array({static_cast<ObjType>(rect.getLower().x()), static_cast<ObjType>(rect.getLower().y()),
                      static_cast<ObjType>(rect.getUpper().x()), static_cast<ObjType>(rect.getUpper().y())});
    }
};
} // namespace charta::pdf