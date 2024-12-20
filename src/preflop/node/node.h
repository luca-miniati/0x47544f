#ifndef NODE_H
#define NODE_H

#include "eval/eval.h"
#include "utils/utils.h"
#include "preflop/solver.h"
#include <string>
#include <algorithm>

// Node in NLHE
class Node {
private:
    // History of actions resulting in this state
    std::vector<ACTION> history;
    std::vector<double> strategy, strategy_sum, regret_sum;

    // Given a history of actions, return the actions that can be taken in this state
    std::vector<ACTION> GetActions(const std::vector<ACTION>& history);
public:
    // Actions available in this state
    std::vector<ACTION> actions;
    bool is_terminal;

    Node(std::vector<ACTION> history);

    // If this node is terminal, return utility of
    // this node to second-to-last player to act
    double GetUtility(std::vector<u32>& deck);

    // Update strategy using regret matching, using p as the reach probability
    // of being in this state
    std::vector<double> GetStrategy(double p);

    // Update regret value
    void UpdateRegret(int a, double v);

    // Return computed strategy at this node
    std::vector<double> GetAverageStrategy();
};

#endif
