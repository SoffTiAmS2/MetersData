cmake_minimum_required(VERSION 3.10)

# Установка имени проекта из имени текущей директории
get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${PROJECT_NAME})

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Пути к исходным и заголовочным файлам
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(LIBS_DIR ${PROJECT_SOURCE_DIR}/external_libs)

# Сбор исходных и заголовочных файлов
file(GLOB_RECURSE SOURCES
    ${SOURCE_DIR}/main.cpp
    "${SOURCE_DIR}/Core/*.cpp"
    "${SOURCE_DIR}/Data/*.cpp"
    "${SOURCE_DIR}/Parsers/*.cpp"
    "${SOURCE_DIR}/utils/*.cpp"
)
# file(INCLUDE "${INCLUDE_DIR}/*.h")

# Подключение директорий для заголовочных файлов
include_directories(${INCLUDE_DIR})

# Создание исполняемого файла
add_executable(${PROJECT_NAME} ${SOURCES})
