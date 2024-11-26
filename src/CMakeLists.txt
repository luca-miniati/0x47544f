add_library(eval_lib
    eval/eval.cc
    eval/eval.h
)

target_include_directories(eval_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
