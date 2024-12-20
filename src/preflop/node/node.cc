#include "../../eval/eval.h"
#include "../../utils/utils.h"
#include "../tree.h"
#include "node.h"
#include <iostream>
#include <string>
#include <algorithm>

std::vector<ACTION> Node::GetActions(const std::vector<ACTION>& history) {
    std::vector<ACTION> actions;
    if (is_terminal)
        return actions;

    // can only check if there's no outstanding bets
    std::pair<double, double> bets = Utils::ComputeTotalBets(history);
    if (bets.first == bets.second)
        actions.push_back(CHECK);
    // we can only call if there's an outstanding bet
    else
        actions.push_back(CALL);

    // we can always fold
    actions.push_back(FOLD);

    // add raises
    int num_raises = 0;
    for (ACTION action : history)
        num_raises += (action == X2 || action == X3 || action == ALL_IN);
    if (num_raises < MAX_RAISE) {
        actions.push_back(X2);
        actions.push_back(X3);
        actions.push_back(ALL_IN);
    }

    return actions;
}

Node::Node(std::vector<ACTION> history) : history(history) {
    // set is_terminal
    is_terminal = history.size() && (history.back() == CALL
                || history.back() == CHECK
                || history.back() == FOLD);

    // compute available actions
    actions = GetActions(history);

    // zero out all arrays
    int num_actions = actions.size();
    regret_sum.resize(num_actions);
    strategy.resize(num_actions);
    for (int a = 0; a < num_actions; ++a)
        strategy[a] = 1.0 / num_actions;
    strategy_sum.resize(num_actions);
};

double Node::GetUtility(std::vector<u32>& deck) {
    // this is 1 if p1 was second to last, 2 otherwise
    int second_to_last = 2 - (history.size() + 1) % 2;
    // compute the amount each player put into the pot
    auto [p1, p2] = Utils::ComputeTotalBets(history);
    if (history.back() == FOLD)
        return (second_to_last == 1) ? p2 * OOP_EQUITY_MULTIPLIER : p1;

    std::vector<u32> p1_cards = {deck[0], deck[1], deck[4], deck[5], deck[6], deck[7], deck[8]};
    std::vector<u32> p2_cards = {deck[2], deck[3], deck[4], deck[5], deck[6], deck[7], deck[8]};
    Eval eval;
    int p1_rank = eval.GetBestHand(p1_cards);
    int p2_rank = eval.GetBestHand(p2_cards);

    double showdown_multiplier;
    if (p1_rank < p2_rank)      showdown_multiplier = 1;
    else if (p1_rank > p2_rank) showdown_multiplier = -1;
    else                        return 0;

    double position_multiplier = (second_to_last == 1 && showdown_multiplier > 0)
                                    ? OOP_EQUITY_MULTIPLIER
                                    : 1;

    return ((second_to_last == 1) ? p2 : p1) * showdown_multiplier * position_multiplier;
}

std::vector<double> Node::GetStrategy(double p) {
    int num_actions = actions.size();
    double norm = 0;
    for (int a = 0; a < num_actions; a++) {
        strategy[a] = fmax(regret_sum[a], 0.0);
        norm += strategy[a];
    }
    for (int a = 0; a < num_actions; a++) {
        if (norm > 0)
            strategy[a] /= norm;
        else
            strategy[a] = 1.0 / num_actions;
        strategy_sum[a] += p * strategy[a];
    }
    return strategy;
}

void Node::UpdateRegret(int a, double v) {
    regret_sum[a] += v;
}

std::vector<double> Node::GetAverageStrategy() {
    int num_actions = actions.size();
    std::vector<double> average_strategy(num_actions);
    double norm = 0;
    for (int a = 0; a < num_actions; ++a)
        norm += strategy_sum[a];
    for (int a = 0; a < num_actions; ++a) {
        if (norm > 0)
        average_strategy[a] = strategy_sum[a] / norm;
        else
        average_strategy[a] = 1.0 / num_actions;
    }
    return average_strategy;
}
