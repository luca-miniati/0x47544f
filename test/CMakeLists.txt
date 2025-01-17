add_executable(
    TestEval
        solver/eval/test_eval.cc
        ../src/solver/game_state/game_state.cc
        ../src/solver/game_state/game_state.h
)
add_executable(
    TestUtils
        solver/utils/test_utils.cc
        ../src/solver/game_state/game_state.cc
        ../src/solver/game_state/game_state.h
)
add_executable(
    TestPreflop
        solver/preflop/node/test_node.cc
        ../src/solver/game_state/game_state.cc
        ../src/solver/game_state/game_state.h
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
