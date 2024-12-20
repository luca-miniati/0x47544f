#ifndef NODE_H
#define NODE_H

#include "../../eval/eval.h"
#include "../../utils/utils.h"
#include "../tree.h"
#include <string>
#include <algorithm>

// Node in NLHE
class Node {
private:
    // History of actions resulting in this state, actions available in this state
    std::vector<ACTION> history, actions;
    std::vector<double> strategy, strategy_sum, regret_sum;

    // Given a history of actions, return the actions that can be taken in this state
    std::vector<ACTION> GetActions(const std::vector<ACTION>& history);
public:
    bool is_terminal;

    Node(std::vector<ACTION> history);

    // If this node is terminal, return utility of
    // this node to second-to-last player to act
    double GetUtility(std::vector<u32>& deck);
};

#endif
