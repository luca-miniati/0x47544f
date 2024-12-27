enable_testing()

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(test_eval solver/eval/test_eval.cc)
add_executable(test_node solver/preflop/node/test_node.cc)
add_executable(test_preflop_action solver/preflop/preflop_action/test_preflop_action.cc)
add_executable(test_utils solver/utils/test_utils.cc)

target_link_libraries(test_eval
        gtest
        gtest_main
        eval_lib
        preflop_lib
        utils_lib
)
target_link_libraries(test_node
        gtest
        gtest_main
        eval_lib
        preflop_lib
        utils_lib
)
target_link_libraries(test_preflop_action
        gtest
        gtest_main
        eval_lib
        preflop_lib
        utils_lib
)
target_link_libraries(test_utils
        gtest
        gtest_main
        eval_lib
        preflop_lib
        utils_lib
)

include(GoogleTest)
gtest_discover_tests(test_eval)
gtest_discover_tests(test_node)
gtest_discover_tests(test_preflop_action)
gtest_discover_tests(test_utils)