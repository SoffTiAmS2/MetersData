file(GLOB_RECURSE SPLITER_SRC "*.cpp")
file(GLOB_RECURSE SPLITER_HEADERS "${INCLUDE_DIR}/core/spliter/**/*.h")

add_library(spliter STATIC ${SPLITER_SRC} ${SPLITER_HEADERS})

target_include_directories(spliter PUBLIC
    ${INCLUDE_DIR}
)

target_link_libraries(spliter PRIVATE Qt6::Core)