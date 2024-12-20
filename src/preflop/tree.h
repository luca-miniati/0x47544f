#ifndef TREE_H
#define TREE_H

// 100 big blinds
constexpr int STACK_DEPTH = 100;
// can't raise more than 4 times
constexpr int MAX_RAISE = 4;
// OOP only realizes 70% of equity post-flop
constexpr double OOP_EQUITY_MULTIPLIER = 0.7;

enum ACTION {
    CHECK,
    CALL,
    FOLD,
    X2,
    X3,
    ALL_IN
};

#endif
