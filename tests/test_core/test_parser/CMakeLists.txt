set(CMAKE_AUTOMOC ON)

add_executable(test_parser test_dateparser.cpp)

target_link_libraries(test_parser PRIVATE Qt6::Test parser model utils)

add_test(NAME test_parser COMMAND test_parser)