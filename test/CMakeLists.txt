add_executable(charta_pdf_tests TestFont.cpp TestWrite.cpp)

if(BUILD_COVERAGE)
    setup_target_for_coverage_lcov(
        NAME charta_pdf_coverage
        EXECUTABLE ctest -j ${n_cores}
        EXCLUDE "contrib/*" "test/*" "bench/*" "/usr/include/*"
        DEPENDENCIES charta_pdf_tests)
endif()

target_compile_definitions(charta_pdf_tests PRIVATE "-DCHARTA_PDF_SOURCE_PATH=\"${CMAKE_SOURCE_DIR}\" ")
target_compile_definitions(charta_pdf_tests PRIVATE "-DCHARTA_PDF_BINARY_PATH=\"${CMAKE_CURRENT_BINARY_DIR}\" ")

target_link_libraries(charta_pdf_tests PRIVATE gtest gtest_main charta_pdf -lstdc++fs)
# Tests may also use the private API
target_include_directories(charta_pdf_tests PRIVATE ${CMAKE_SOURCE_DIR}/src)

include(GoogleTest)
gtest_discover_tests(charta_pdf_tests)