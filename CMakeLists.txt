cmake_minimum_required(VERSION 3.5)

project(BatteryTest LANGUAGES CXX VERSION 0.0.1)

find_package(Catch2 REQUIRED)

add_executable(battery_test 
    test-alerts.cpp
    typewise-alert.cpp)
target_link_libraries(battery_test PRIVATE Catch2::Catch2)

include(CTest)
include(Catch)
catch_discover_tests(battery_test)