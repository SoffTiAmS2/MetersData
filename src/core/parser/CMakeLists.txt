file(GLOB_RECURSE PARSER_SRC "*.cpp")
file(GLOB_RECURSE PARSER_HEADERS "${INCLUDE_DIR}/core/parser/**/*.h")

add_library(parser STATIC ${PARSER_SRC} ${PARSER_HEADERS})

target_include_directories(parser PUBLIC
    ${INCLUDE_DIR}
)

target_link_libraries(parser PRIVATE Qt6::Core model utils)