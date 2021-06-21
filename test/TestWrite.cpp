#include <charta/Document.hpp>
#include <filesystem>
#include <gtest/gtest.h>

using namespace charta::pdf;

TEST(Write, Meta)
{
    auto outFile = std::string(CHARTA_PDF_BINARY_PATH) + "/test_empty_write.pdf";

    Document doc;

    Info info;
    info.Title = "Test document";
    info.Subject = "Testing";
    info.Author = "Stephan Vedder";
    doc.setInfo(info);

    EXPECT_TRUE(doc.saveToFile(outFile));
}

TEST(Write, Page)
{
    auto outFile = std::string(CHARTA_PDF_BINARY_PATH) + "/test_page_write.pdf";

    Document doc;

    Page first;
    doc.addPage(first);

    EXPECT_TRUE(doc.saveToFile(outFile));
}