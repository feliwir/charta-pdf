#pragma once

namespace charta::pdf
{
struct ObjectWriteInformation
{
    bool written = false;
    size_t write_pos = 0;
    size_t id = 0;
};
} // namespace charta::pdf