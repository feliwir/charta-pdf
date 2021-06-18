#pragma once
#include <optional>
#include <string>

namespace charta::pdf
{
class FontDescriptor
{
  private:
    std::string m_name;
    std::string m_family;
    std::optional<uint16_t> m_weight;
};
} // namespace charta::pdf