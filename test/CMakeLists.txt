add_executable(
    TestEval
    eval/test_eval.cc
)
add_executable(
    TestUtils
    utils/test_utils.cc
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

add_test(NAME TestEval COMMAND TestEval)
add_test(NAME TestUtils COMMAND TestUtils)
