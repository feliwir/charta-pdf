#include <charta/PDFDocument.hpp>
#include <filesystem>
#include <gtest/gtest.h>

using namespace charta::pdf;

TEST(Document, Write)
{
    auto outFile = std::string(CHARTA_PDF_BINARY_PATH) + "/test_write.pdf";

    PDFDocument doc;
    EXPECT_TRUE(doc.saveTo(outFile));
}