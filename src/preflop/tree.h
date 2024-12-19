#ifndef TREE_H
#define TREE_H

// 100 big blinds
const int STACK_DEPTH = 100;
// can't raise more than 4 times
const int MAX_BET = 4;

// assuming SB vs BB
enum ACTIONS {
    CHECK,
    CALL,
    FOLD,
    ALL_IN,
    X2,
    X3,
};

#endif
