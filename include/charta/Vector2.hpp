#pragma once
#include <string>

namespace charta::pdf
{
template <class T> class Vector2
{
  private:
    T m_x = 0;
    T m_y = 0;

  public:
    inline Vector2() = default;
    inline Vector2(T v) : m_x(v), m_y(v)
    {
    }
    inline Vector2(T x, T y) : m_x(x), m_y(y)
    {
    }

    inline std::string toString() const
    {
        return std::to_string(m_x) + "." + std::to_string(m_y);
    }

    inline T &x()
    {
        return m_x;
    }
    inline T &y()
    {
        return m_y;
    }
};

using Vector2i = Vector2<int>;
using Vector2f = Vector2<float>;
using Vector2u = Vector2<unsigned>;
} // namespace charta::pdf