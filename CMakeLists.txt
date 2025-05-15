cmake_minimum_required(VERSION 3.10)
project(MetersData LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# === Включаем автоматическую генерацию moc/uic/rcc
# set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
# set(CMAKE_AUTORCC ON)



# === Пути проекта
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(FORMS_DIR ${PROJECT_SOURCE_DIR}/forms)
set(RESOURCES_DIR ${PROJECT_SOURCE_DIR}/res)
set(LIBS_DIR ${PROJECT_SOURCE_DIR}/external_libs)

# === Поддержка macOS
if(APPLE)
    set(CMAKE_MACOSX_RPATH 1)
    set(CMAKE_MACOSX_BUNDLE ON)
    set(CMAKE_OSX_DEPLOYMENT_TARGET "11.0")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework AppKit")
endif()

# === Поиск Qt6
find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui UiTools Test)

# === ICU
set(ICU_INCLUDE_DIR "${LIBS_DIR}/icu4c/include")
set(ICU_LIB_DIR "${LIBS_DIR}/icu4c/lib")
include_directories(${ICU_INCLUDE_DIR})
link_directories(${ICU_LIB_DIR})
set(ICU_LIBS icuuc icui18n)

# === Добавляем подпроекты
add_subdirectory(src/core/model)
add_subdirectory(src/core/spliter)
add_subdirectory(src/core/parser)
add_subdirectory(src/core/file)
add_subdirectory(src/core/factory)
add_subdirectory(src/utils)
add_subdirectory(src/controller)
add_subdirectory(src/view)

# === Собираем основное приложение
file(GLOB_RECURSE SOURCES ${SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE HEADERS ${INCLUDE_DIR}/*.h)
file(GLOB_RECURSE RESOURCES ${RESOURCES_DIR}/*.qrc)

set(CMAKE_AUTOUIC_SEARCH_PATHS ${PROJECT_SOURCE_DIR}/forms)

add_executable(${PROJECT_NAME} MACOSX_BUNDLE ${SOURCES} ${HEADERS} ${RESOURCES})

# === Линковка
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Qt6::Widgets
        Qt6::Gui
        Qt6::Core
        Qt6::UiTools
        Qt6::Test
        model
        spliter
        parser
        file
        factory
        utils
        controller
        view
        ${ICU_LIBS}
)

target_include_directories(${PROJECT_NAME} PRIVATE ${ICU_INCLUDE_DIR})


enable_testing()
add_subdirectory(tests)