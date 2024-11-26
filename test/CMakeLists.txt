add_executable(
    TestEval
    eval/test_eval.cc
)

target_link_libraries(
    TestEval
    PUBLIC
    eval_lib
)

add_test(NAME TestEval COMMAND TestEval)
