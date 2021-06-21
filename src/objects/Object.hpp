#pragma once
#include "IndirectObject.hpp"
#include "IntegerObject.hpp"
#include "LiteralString.hpp"
#include "NameObject.hpp"
#include "RealObject.hpp"
#include <variant>

namespace charta::pdf
{
class Array;
class Dictionary;
using Object = std::variant<NameObject, IntegerObject, RealObject, IndirectObject, LiteralString, Dictionary, Array>;
} // namespace charta::pdf