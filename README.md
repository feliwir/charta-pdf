# charta-pdf

A modern C++ library for processing **PDF** documents.

## Build status
[![CI](https://github.com/feliwir/charta-pdf/actions/workflows/ci.yml/badge.svg)](https://github.com/feliwir/charta-pdf/actions/workflows/ci.yml)
[![codecov](https://codecov.io/gh/feliwir/charta-pdf/branch/master/graph/badge.svg?token=2XKMBCI2MR)](https://codecov.io/gh/feliwir/charta-pdf)

## Example

How to write an empty PDF file with metainformation:
```c++
#include <charta/Document.hpp>

void savePdf(std::string_view filepath)
{
  charta::pdf::Document doc;

  charta::pdf::Info info;
  info.Author = "Stephan Vedder";
  doc.setInfo(info);
  doc.saveToFile(filepath);
}
```
