#include "../../../src/eval/eval.h"
#include "../../../src/utils/utils.h"
#include "../../../src/preflop/node/node.h"
#include "preflop/tree.h"
#include <iostream>
#include <cassert>
#include <stdexcept>
#include <vector>
#include <string>

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
