#pragma once
#include <chrono>
#include <string>
#include <string_view>

namespace charta::pdf
{
struct Info
{
  public:
    std::string Title;
    std::string Author;
    std::string Subject;
    std::string Keywords;
    std::string Creator;
    std::string Producer;
    std::chrono::time_point<std::chrono::system_clock> CreationDate;
    std::chrono::time_point<std::chrono::system_clock> ModDate;
};
} // namespace charta::pdf