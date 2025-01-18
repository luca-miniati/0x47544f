enable_testing()

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)

target_link_libraries(
        TestEval
        PUBLIC
        eval_lib
        utils_lib
)
target_link_libraries(
        TestUtils
        PUBLIC
        eval_lib
        utils_lib
)
target_link_libraries(
        TestPreflop
        PUBLIC
        eval_lib
        utils_lib
        preflop_lib
)

add_test(NAME TestEval COMMAND TestEval)
add_test(NAME TestUtils COMMAND TestUtils)
add_test(NAME TestPreflop COMMAND TestPreflop)
