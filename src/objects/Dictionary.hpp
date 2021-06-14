#pragma once
#include <map>
#include <variant>

#include "IndirectObject.hpp"
#include "LiteralString.hpp"
#include "NameObject.hpp"

namespace charta::pdf
{
using DictValue = std::variant<NameObject, int, IndirectObject, LiteralString>;
using Dictionary = std::map<std::string, DictValue>;
} // namespace charta::pdf