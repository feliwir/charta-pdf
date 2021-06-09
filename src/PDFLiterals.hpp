#pragma once
#include <string_view>

namespace charta::pdf
{
constexpr const char PDF_COMMENT_PREFIX = '%';
constexpr const char *PDF_NEWLINE = "\r\n";

// Comments
constexpr const char *PDF_COMMENT_EOF = "%EOF";

// Keywords
constexpr const char *PDF_KEYWORD_TRAILER = "trailer";
constexpr const char *PDF_KEYWORD_XREF = "xref";
constexpr const char *PDF_KEYWORD_STARTXREF = "startxref";
constexpr const char *PDF_KEYWORD_OBJECT = "obj";
constexpr const char *PDF_KEYWORD_END_OBJECT = "obj";

// Dictionary
constexpr const char *PDF_DICT_KEY_SIZE = "Size";
constexpr const char *PDF_DICT_KEY_TYPE = "Type";

constexpr const char *PDF_DICT_VALUE_CATALOG = "Catalog";

} // namespace charta::pdf