file(GLOB_RECURSE MODEL_SRC "*.cpp")
file(GLOB_RECURSE MODEL_HEADERS "${INCLUDE_DIR}/core/model/**/*.h")

add_library(model STATIC ${MODEL_SRC} ${MODEL_HEADERS})

target_include_directories(model PUBLIC
    ${INCLUDE_DIR}
)
