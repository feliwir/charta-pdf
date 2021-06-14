#pragma once
#include <string_view>

namespace charta::pdf
{
constexpr const char PDF_COMMENT_PREFIX = '%';
constexpr const char PDF_SLASH = '/';
constexpr const char PDF_REFERENCE_SUFFIX = 'R';
constexpr const char PDF_TABULATOR = '\t';
constexpr const char *PDF_NEWLINE = "\r\n";

// Comments
constexpr const char *PDF_COMMENT_EOF = "%EOF";

// Keywords
constexpr const char *PDF_KEYWORD_TRAILER = "trailer";
constexpr const char *PDF_KEYWORD_XREF = "xref";
constexpr const char *PDF_KEYWORD_STARTXREF = "startxref";
constexpr const char *PDF_KEYWORD_OBJECT = "obj";
constexpr const char *PDF_KEYWORD_END_OBJECT = "endobj";

// Dictionary
constexpr const char *PDF_DICT_START = "<<";
constexpr const char *PDF_DICT_END = ">>";

// Keys
constexpr const char *PDF_DICT_KEY_SIZE = "Size";
constexpr const char *PDF_DICT_KEY_TYPE = "Type";

// Trailer references
constexpr const char *PDF_DICT_KEY_ROOT = "Root";
constexpr const char *PDF_DICT_KEY_INFO = "Info";

// Info dictionaries keys
constexpr const char *PDF_DICT_KEY_INFO_AUTHOR = "Author";
constexpr const char *PDF_DICT_KEY_INFO_TITLE = "Title";

// Dictionary types
constexpr const char *PDF_DICT_VALUE_CATALOG = "Catalog";

} // namespace charta::pdf