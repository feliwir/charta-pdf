#include <charta/Document.hpp>
#include <filesystem>
#include <gtest/gtest.h>

using namespace charta::pdf;

TEST(Font, TrueType)
{
    auto outFile = std::string(CHARTA_PDF_BINARY_PATH) + "/test_font_truetype.pdf";
    auto inFont = std::string(CHARTA_PDF_SOURCE_PATH) + "/test/fonts/Roboto-Regular.ttf";

    Document doc;
    EXPECT_NE(doc.addFontFromFile(inFont), nullptr);

    EXPECT_TRUE(doc.saveToFile(outFile));
}