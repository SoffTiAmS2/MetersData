file(GLOB_RECURSE FILE_SRC "*.cpp")
file(GLOB_RECURSE FILE_HEADERS "${INCLUDE_DIR}/core/file/**/*.h")

add_library(file STATIC ${FILE_SRC} ${FILE_HEADERS})

target_include_directories(file PUBLIC
    ${INCLUDE_DIR}
)

target_link_libraries(file PRIVATE Qt6::Core model parser)