#include <charta/Document.hpp>
#include <filesystem>
#include <gtest/gtest.h>

using namespace charta::pdf;

TEST(Document, Write)
{
    auto outFile = std::string(CHARTA_PDF_BINARY_PATH) + "/test_write.pdf";

    Document doc;

    Info info;
    info.Title = "Test document";
    info.Subject = "Testing";
    info.Author = "Stephan Vedder";
    doc.setInfo(info);

    EXPECT_TRUE(doc.saveToFile(outFile));
}