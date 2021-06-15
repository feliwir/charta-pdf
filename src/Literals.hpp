#pragma once
#include <string_view>

namespace charta::pdf
{
// Whitespace characters
constexpr const char PDF_HORIZONTAL_TAB = '\t';
constexpr const char PDF_LINE_FEED = '\n';
constexpr const char PDF_CARRIAGE_RETURN = '\r';
constexpr const char PDF_EOL[] = {PDF_CARRIAGE_RETURN, PDF_LINE_FEED};
constexpr const char PDF_SPACE = ' ';

// Delimiters
constexpr const char PDF_LEFT_PARENTHESIS = '(';
constexpr const char PDF_RIGHT_PARENTHESIS = ')';
constexpr const char PDF_LESS_THAN = '<';
constexpr const char PDF_GREATER_THAN = '>';
constexpr const char PDF_SOLIDUS = '/';
constexpr const char PDF_PERCENT_SIGN = '%';

// Suffixes
constexpr const char PDF_REFERENCE_SUFFIX = 'R';

// Comments
constexpr const char *PDF_COMMENT_EOF = "%EOF";

// Keywords
constexpr const char *PDF_KEYWORD_TRAILER = "trailer";
constexpr const char *PDF_KEYWORD_XREF = "xref";
constexpr const char *PDF_KEYWORD_STARTXREF = "startxref";
constexpr const char *PDF_KEYWORD_OBJECT = "obj";
constexpr const char *PDF_KEYWORD_END_OBJECT = "endobj";

// Dictionary
constexpr const char PDF_DICT_START[] = {PDF_LESS_THAN, PDF_LESS_THAN, '\0'};
constexpr const char PDF_DICT_END[] = {PDF_GREATER_THAN, PDF_GREATER_THAN, '\0'};

// Keys
constexpr const char *PDF_DICT_KEY_PARENT = "Parent";
constexpr const char *PDF_DICT_KEY_SIZE = "Size";
constexpr const char *PDF_DICT_KEY_TYPE = "Type";

// Trailer references
constexpr const char *PDF_DICT_KEY_ROOT = "Root";
constexpr const char *PDF_DICT_KEY_INFO = "Info";

// Info dictionaries keys
constexpr const char *PDF_DICT_KEY_INFO_TITLE = "Title";
constexpr const char *PDF_DICT_KEY_INFO_AUTHOR = "Author";
constexpr const char *PDF_DICT_KEY_INFO_SUBJECT = "Subject";
constexpr const char *PDF_DICT_KEY_INFO_KEYWORDS = "Keywords";
constexpr const char *PDF_DICT_KEY_INFO_CREATOR = "Creator";
constexpr const char *PDF_DICT_KEY_INFO_PRODUCER = "Producer";

// Dictionary types
constexpr const char *PDF_DICT_VALUE_TYPE_PAGE = "Page";
constexpr const char *PDF_DICT_VALUE_TYPE_PAGES = "Pages";
constexpr const char *PDF_DICT_VALUE_TYPE_CATALOG = "Catalog";

} // namespace charta::pdf