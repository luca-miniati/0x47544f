include_directories(${CMAKE_SOURCE_DIR}/src)

add_library(eval_lib
    eval/eval.cc
)

target_include_directories(eval_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(utils_lib
    utils/utils.cc
)

target_include_directories(utils_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(preflop_lib
    preflop/node/node.cc
)

target_include_directories(preflop_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
