# charta-pdf

A modern C++ 17 library for processing **PDF** documents.

## Build status
[![CI](https://github.com/feliwir/charta-pdf/actions/workflows/ci.yml/badge.svg)](https://github.com/feliwir/charta-pdf/actions/workflows/ci.yml)
[![codecov](https://codecov.io/gh/feliwir/charta-pdf/branch/master/graph/badge.svg?token=2XKMBCI2MR)](https://codecov.io/gh/feliwir/charta-pdf)
 [![License: MIT](https://img.shields.io/badge/License-MIT-brightgreen.svg)](https://opensource.org/licenses/MIT)
## Example

How to write an PDF file with metainformation and a single page:
```c++
#include <charta/Document.hpp>
using namespace charta::pdf;

void savePdf(std::string_view filepath)
{
  Document doc;
  // Set the meta information
  Info info;
  info.Author = "Stephan Vedder";
  doc.setInfo(info);
  // Add a page
  Page page(presets::A4Paper_Portrait);
  doc.addPage(page);
  // Write it out
  doc.saveToFile(filepath);
}
```
