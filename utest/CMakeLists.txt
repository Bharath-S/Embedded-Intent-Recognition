cmake_minimum_required(VERSION 3.19)

file(GLOB_RECURSE Sources CONFIGURE_DEPENDS "*.cpp")

add_executable(uTest ${Sources})
target_link_libraries(uTest PUBLIC
    gtest_main
    EmbeddedIntentRecogniserLib
)

add_test(
    NAME uTest
    COMMAND uTest
)
