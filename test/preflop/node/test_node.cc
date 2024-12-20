#include "../../../src/eval/eval.h"
#include "../../../src/utils/utils.h"
#include "../../../src/preflop/node/node.h"
#include "preflop/tree.h"
#include <iostream>
#include <cassert>
#include <stdexcept>
#include <vector>
#include <string>

// Test constructor behaviors of Node.
void test_constructor() {
    // Tests for is_terminal

    // shouldn't be terminal at the start
    Node* node = new Node({});
    assert(!node->is_terminal && "WA on is_terminal empty history");
    // shouldn't be terminal after one bet
    node = new Node({X2});
    assert(!node->is_terminal && "WA on is_terminal on raise");
    // shouldn't be terminal after one raise
    node = new Node({X2, X3});
    assert(!node->is_terminal && "WA on is_terminal bet raise");
    // shouldn't be terminal after a jam
    node = new Node({ALL_IN});
    assert(!node->is_terminal && "WA on is_terminal jam");

    // should be terminal after action goes raise call
    node = new Node({X2, CALL});
    assert(node->is_terminal && "WA on is_terminal bet call");
    // should be terminal after action goes raise re-raise call
    node = new Node({X2, X3, CALL});
    assert(node->is_terminal && "WA on is_terminal re re-raise call");
    // should be terminal after action goes raise re-raise fold
    node = new Node({X2, X3, FOLD});
    assert(node->is_terminal && "WA on is_terminal raise re-raise fold");
    // should be terminal after action goes jam fold
    node = new Node({ALL_IN, FOLD});
    assert(node->is_terminal && "WA on is_terminal jam fold");
    // should be terminal after action goes call check
    node = new Node({CALL, CHECK});
    assert(node->is_terminal && "WA on is_terminal call check");


    // Tests for GetActions
    // should have all except for check
    node = new Node({});
    std::vector<ACTION> expected = {CALL, FOLD, X2, X3, ALL_IN};
    assert(expected == node->actions && "WA on actions empty history");
    // should have all except for check
    node = new Node({X2});
    expected = {CALL, FOLD, X2, X3, ALL_IN};
    assert(expected == node->actions && "WA on actions on raise");
    // should have all except for check
    node = new Node({X2, X3});
    expected = {CALL, FOLD, X2, X3, ALL_IN};
    assert(expected == node->actions && "WA on actions bet raise");
    // should have all except for check
    node = new Node({ALL_IN});
    expected = {CALL, FOLD, X2, X3, ALL_IN};
    assert(expected == node->actions && "WA on actions jam");

    // should have no actions on terminal node
    node = new Node({X2, CALL});
    expected = {};
    assert(expected == node->actions && "WA on actions bet call");
    // should have no actions on terminal node
    node = new Node({X2, X3, CALL});
    assert(expected == node->actions && "WA on actions re re-raise call");
    // should have no actions on terminal node
    node = new Node({X2, X3, FOLD});
    assert(expected == node->actions && "WA on actions raise re-raise fold");
    // should have no actions on terminal node
    node = new Node({ALL_IN, FOLD});
    assert(expected == node->actions && "WA on actions jam fold");
    // should have no actions on terminal node
    node = new Node({CALL, CHECK});
    assert(expected == node->actions && "WA on actions call check");
}

// Test the GetUtility function that returns the payoff for a terminal state.
void test_get_utility() {
    // SB folds aces preflop
    std::vector<u32> deck = {Utils::ParseCards("AcAdAhAs2c2d2h2s3c")};
    Node* node = new Node({FOLD});
    assert(0.5 == node->GetUtility(deck) && "WA on SB fold");

    // SB calls, BB checks
    deck = {Utils::ParseCards("AcAdAhAs2c2d2h2s3c")};
    node = new Node({CALL, CHECK});
    assert(0 == node->GetUtility(deck) && "WA on call check");

    // SB calls, BB checks
    deck = {Utils::ParseCards("AcAdAhJs5d6d7d8cTs")};
    node = new Node({CALL, CHECK});
    assert(OOP_EQUITY_MULTIPLIER == node->GetUtility(deck) && "WA on call check SB win");

    // SB raise, BB raise, SB raise, BB call
    deck = {Utils::ParseCards("KcKdAhAs5d6d7d8cTs")};
    node = new Node({X2, X2, X2, CALL});
    assert(-8 == node->GetUtility(deck));

    // SB raise, BB raise, SB fold
    deck = {Utils::ParseCards("KcKdAhAs5d6d7d8cTs")};
    node = new Node({X3, X2, FOLD});
    assert(3 == node->GetUtility(deck));

    // SB limps, BB raise, SB limp raises, BB folds aces
    deck = {Utils::ParseCards("KcKdAhAs5d6d7d8cTs")};
    node = new Node({CALL, X2, X3, FOLD});
    assert(2 * OOP_EQUITY_MULTIPLIER == node->GetUtility(deck));
}

int main() {
    test_get_utility();
}
