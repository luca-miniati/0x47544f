include_directories(${CMAKE_SOURCE_DIR}/src)

add_library(eval_lib
        solver/eval/eval.cc
        solver/preflop/preflop_solver.cc
        solver/preflop/preflop_solver.h
        solver/preflop/preflop_action/preflop_action.cc
        solver/preflop/preflop_action/preflop_action.h
        solver/preflop/range/range.cc
        solver/preflop/range/range.h
)

target_include_directories(eval_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(utils_lib
        solver/utils/utils.cc
)

target_include_directories(utils_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(preflop_lib
        solver/preflop/node/node.h
        solver/preflop/preflop_solver.cc
        solver/preflop/preflop_solver.h
        solver/preflop/preflop_action/preflop_action.cc
        solver/preflop/preflop_action/preflop_action.h
        solver/preflop/range/range.cc
        solver/preflop/range/range.h
        solver/preflop/game_state/game_state.cc
        solver/preflop/game_state/game_state.h
)

target_include_directories(preflop_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
