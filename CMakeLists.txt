cmake_minimum_required(VERSION 3.16)
project(GodOfWar1Xbox360Port LANGUAGES CXX)

option(GOW1_BUILD_TESTS "Build portable unit tests" ON)

add_library(gow1_common INTERFACE)
target_include_directories(gow1_common INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_compile_features(gow1_common INTERFACE cxx_std_11)

if(GOW1_BUILD_TESTS)
    enable_testing()
    add_executable(ps2_memory_test tests/ps2_memory_test.cpp)
    target_link_libraries(ps2_memory_test PRIVATE gow1_common)
    add_test(NAME ps2_memory_test COMMAND ps2_memory_test)

    add_executable(ee_cpu_state_test tests/ee_cpu_state_test.cpp)
    target_link_libraries(ee_cpu_state_test PRIVATE gow1_common)
    add_test(NAME ee_cpu_state_test COMMAND ee_cpu_state_test)

    add_executable(ee_integer_ops_test tests/ee_integer_ops_test.cpp)
    target_link_libraries(ee_integer_ops_test PRIVATE gow1_common)
    add_test(NAME ee_integer_ops_test COMMAND ee_integer_ops_test)
endif()
