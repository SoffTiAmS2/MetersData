add_executable(test_controller test_metercontroller.cpp)

target_link_libraries(test_controller PRIVATE Qt6::Test controller model file)

add_test(NAME test_controller COMMAND test_controller)