include_directories(${CMAKE_SOURCE_DIR}/src)

add_library(eval_lib
        solver/eval/eval.cc
        solver/eval/eval.h
        solver/actions/fold.cc
        solver/actions/fold.h
        solver/actions/check.cc
        solver/actions/check.h
        solver/actions/call.cc
        solver/actions/call.h
        solver/actions/all_in.cc
        solver/actions/all_in.h
        solver/actions/bet.cc
        solver/actions/bet.h
        solver/actions/raise.cc
        solver/actions/raise.h
)

target_include_directories(eval_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(utils_lib
        solver/utils/utils.cc
        solver/utils/utils.h
)

target_include_directories(utils_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(preflop_lib
        solver/node/node.cc
        solver/node/node.h
        solver/utils/preflop_solver.cc
        solver/utils/preflop_solver.h
        solver/preflop/preflop_action/preflop_action.cc
        solver/preflop/preflop_action/preflop_action.h
        solver/range/range.cc
        solver/range/range.h
        solver/actions/action.h
)

target_include_directories(preflop_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
