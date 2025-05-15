set(CMAKE_AUTOMOC ON)

file(GLOB_RECURSE CONTROLLER_SRC "*.cpp")
file(GLOB_RECURSE CONTROLLER_HEADERS "${INCLUDE_DIR}/controller/*.h")

add_library(controller STATIC ${CONTROLLER_SRC} ${CONTROLLER_HEADERS})

target_include_directories(controller PUBLIC
    ${INCLUDE_DIR}
)

target_link_libraries(controller PRIVATE Qt6::Core model file)