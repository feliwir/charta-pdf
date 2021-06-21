find_package(Freetype REQUIRED)

add_library(charta_pdf)

target_link_libraries(charta_pdf Freetype::Freetype)
target_include_directories(charta_pdf PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_sources(charta_pdf PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/Document.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/fonts/FreetypeFont.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/fonts/FreetypeHelper.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Writer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/write/ObjectWriter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/write/PrimitiveWriter.cpp)