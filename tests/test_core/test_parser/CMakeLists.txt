set(CMAKE_AUTOMOC ON)
add_executable(test_dateparser test_dateparser.cpp)
target_link_libraries(test_dateparser PRIVATE Qt6::Test parser model utils)
add_test(NAME test_dateparser COMMAND test_dateparser)