file(GLOB_RECURSE FACTORY_SRC "*.cpp")
file(GLOB_RECURSE FACTORY_HEADERS "${INCLUDE_DIR}/core/factory/**/*.h")

add_library(factory STATIC ${FACTORY_SRC} ${FACTORY_HEADERS})

target_include_directories(factory PUBLIC
    ${INCLUDE_DIR}
)

target_link_libraries(factory PRIVATE Qt6::Core model)