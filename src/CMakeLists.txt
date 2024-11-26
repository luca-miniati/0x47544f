add_library(eval_lib
    eval.cc
    eval.h
)

target_include_directories(eval PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
