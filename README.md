# charta-pdf

A modern C++ library for processing **PDF** documents.

## Build status
[![CI](https://github.com/feliwir/charta-pdf/actions/workflows/ci.yml/badge.svg)](https://github.com/feliwir/charta-pdf/actions/workflows/ci.yml)
[![codecov](https://codecov.io/gh/feliwir/charta-pdf/branch/master/graph/badge.svg?token=2XKMBCI2MR)](https://codecov.io/gh/feliwir/charta-pdf)
 [![License: MIT](https://img.shields.io/badge/License-MIT-brightgreen.svg)](https://opensource.org/licenses/MIT)
## Example

How to write an PDF file with metainformation and a single page:
```c++
#include <charta/Document.hpp>

void savePdf(std::string_view filepath)
{
  charta::pdf::Document doc;
  // Set the meta information
  charta::pdf::Info info;
  info.Author = "Stephan Vedder";
  doc.setInfo(info);
  // Add a page
  charta::pdf::Page page(charta::pdf::presets::A4Paper_Portrait);
  doc.addPage(page);
  // Write it out
  doc.saveToFile(filepath);
}
```
