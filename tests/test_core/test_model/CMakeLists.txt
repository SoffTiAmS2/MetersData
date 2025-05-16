set(CMAKE_AUTOMOC ON)

add_executable(test_abstractmeter test_abstractmeter.cpp)
target_link_libraries(test_abstractmeter PRIVATE Qt6::Test model utils)
add_test(NAME test_abstractmeter COMMAND test_abstractmeter)

set(CMAKE_AUTOMOC ON)
add_executable(test_date test_date.cpp)
target_link_libraries(test_date PRIVATE Qt6::Test model utils)
add_test(NAME test_date COMMAND test_date)

set(CMAKE_AUTOMOC ON)
add_executable(test_meter test_meter.cpp)
target_link_libraries(test_meter PRIVATE Qt6::Test model utils)
add_test(NAME test_meter COMMAND test_meter)

set(CMAKE_AUTOMOC ON)
add_executable(test_meterlist test_meterlist.cpp)
target_link_libraries(test_meterlist PRIVATE Qt6::Test model utils)
add_test(NAME test_meterlist COMMAND test_meterlist)