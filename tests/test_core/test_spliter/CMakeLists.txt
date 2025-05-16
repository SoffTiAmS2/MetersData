set(CMAKE_AUTOMOC ON)
add_executable(test_stringsplitter test_stringsplitter.cpp)
target_link_libraries(test_stringsplitter PRIVATE Qt6::Test spliter utils)
add_test(NAME test_stringsplitter COMMAND test_stringsplitter)