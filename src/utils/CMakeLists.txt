file(GLOB_RECURSE UTILS_SRC "*.cpp")
file(GLOB_RECURSE UTILS_HEADERS "${INCLUDE_DIR}/utils/**/*.h")

add_library(utils STATIC ${UTILS_SRC} ${UTILS_HEADERS})

target_include_directories(utils PUBLIC
    ${INCLUDE_DIR}
)

target_link_libraries(utils PRIVATE Qt6::Core ${ICU_LIBS})