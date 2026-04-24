cmake_minimum_required(VERSION 3.14)

add_executable(banking_tests
    ${CMAKE_CURRENT_SOURCE_DIR}/test_account.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test_transaction.cpp
)

target_include_directories(banking_tests PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(banking_tests PRIVATE
    banking
    gtest
    gtest_main
    gmock
    gmock_main
    pthread
)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(banking_tests PRIVATE --coverage)
    target_link_options(banking_tests PRIVATE --coverage)
endif()

include(GoogleTest)
gtest_discover_tests(banking_tests)
