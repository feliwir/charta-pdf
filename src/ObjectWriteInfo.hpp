#pragma once
#include "ObjectReference.hpp"

namespace charta::pdf
{
struct ObjectWriteInformation
{
    bool written = false;
    size_t write_pos;
    ObjectReference id;
};
} // namespace charta::pdf