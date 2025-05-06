cmake_minimum_required(VERSION 3.10)
# Получаем имя проекта из имени текущей директории
get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${PROJECT_NAME})

# Включаем автоматическую обработку UI, MOC и ресурсов
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Для macOS: создаём .app и задаём параметры деплоя
if(APPLE)
    message(STATUS "Building for macOS")
    set(CMAKE_MACOSX_RPATH 1)
    set(CMAKE_MACOSX_BUNDLE ON)
    set(CMAKE_OSX_DEPLOYMENT_TARGET "11.0")  # Минимальная поддерживаемая версия macOS
    set(CMAKE_EXE_LINKER_FLAGS "-framework AppKit")
endif()

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Пути к исходным файлам, заголовкам и UI-файлам
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(FORMS_DIR ${CMAKE_SOURCE_DIR}/forms)
set(RESOURCES_DIR ${CMAKE_SOURCE_DIR}/res)
set(LIBS_DIR ${PROJECT_SOURCE_DIR}/external_libs)

# Добавляем директорию с заголовками
include_directories(${INCLUDE_DIR})

# Собираем файлы
file(GLOB_RECURSE SOURCES
    ${SOURCE_DIR}/*.cpp
    ${SOURCE_DIR}/*/*.cpp
    ${SOURCE_DIR}/*/*/*.cpp
)
file(GLOB_RECURSE INCLUDE "${INCLUDE_DIR}/*.h")
file(GLOB_RECURSE FORMS "${FORMS_DIR}/*.ui")
file(GLOB_RECURSE RESOURCES "${RESOURCES_DIR}/*.qrc")

# Выводим отладочную информацию
message(STATUS "Sources: ${SOURCES}")
message(STATUS "Forms: ${FORMS}")
message(STATUS "Resources: ${RESOURCES}")

# Указываем, где искать UI-файлы для AUTOUIC
set(CMAKE_AUTOUIC_SEARCH_PATHS ${FORMS_DIR})

# Находим компоненты Qt6
find_package(Qt6 COMPONENTS Widgets Core Gui UiTools REQUIRED)
if(NOT Qt6_FOUND)
    message(FATAL_ERROR "Qt6 не найден!")
endif()

# Добавление модулей

# Создание исполняемого файла в виде .app
add_executable(${PROJECT_NAME} MACOSX_BUNDLE ${SOURCES} ${INCLUDE} ${FORMS} ${RESOURCES})

# Линковка с Qt
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets Qt6::Core Qt6::Gui Qt6::UiTools)

# Подключаем include директории
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR})