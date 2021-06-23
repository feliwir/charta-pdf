#pragma once
#include <stdint.h>
#include <vector>

namespace charta::pdf
{
enum class Filter
{
    None,
    Deflate
};

class Stream
{
  private:
    Filter m_filter = Filter::None;
    std::vector<uint8_t> m_data;

  public:
    inline const std::vector<uint8_t> &getData()
    {
        return m_data;
    }
    const std::vector<uint8_t> calculateFilteredData();

    const Filter getFilter()
    {
        return m_filter;
    }
};
} // namespace charta::pdf