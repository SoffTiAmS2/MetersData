# src/view/CMakeLists.txt

set(CMAKE_AUTOMOC ON)

file(GLOB_RECURSE VIEW_SRC "${SOURCE_DIR}/view/ui/*.cpp")
file(GLOB_RECURSE VIEW_HEADERS "${INCLUDE_DIR}/view/ui/*.h")

set(CMAKE_AUTOUIC_SEARCH_PATHS ${PROJECT_SOURCE_DIR}/forms)

add_library(view STATIC ${VIEW_SRC} ${VIEW_HEADERS})


message(STATUS "UI файлы ищутся в: ${VIEW_HEADERS}")
message(STATUS "UI файлы ищутся в: ${FORMS_DIR}")
message(STATUS "Сгенерированные UI файлы будут здесь: ${CMAKE_CURRENT_BINARY_DIR}/view_autogen/include")

target_link_libraries(view PRIVATE Qt6::Widgets controller)