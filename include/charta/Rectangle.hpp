#pragma once
#include "Vector2.hpp"
#include <string>

namespace charta::pdf
{
template <class T> class Rectangle
{
  private:
    const Vector2<T> m_lower = 0;
    const Vector2<T> m_upper = 0;

  public:
    inline Rectangle() = default;
    inline constexpr Rectangle(const Vector2<T> &lower, const Vector2<T> &upper) : m_lower(lower), m_upper(upper)
    {
    }
    inline Rectangle(T lx, T ly, T ux, T uy) : m_lower(lx, ly), m_upper(ux, uy)
    {
    }

    inline const Vector2<T> &getLower() const
    {
        return m_lower;
    }

    inline const Vector2<T> &getUpper() const
    {
        return m_upper;
    }
};

using Rectanglei = Rectangle<int>;
using Rectanglef = Rectangle<float>;
using Rectangleu = Rectangle<unsigned>;
} // namespace charta::pdf