#include "solver/eval/eval.h"
#include "solver/utils/utils.h"
#include "solver/preflop/preflop_action/preflop_action.h"
#include "node.h"

std::vector<std::shared_ptr<PreflopAction>> Node::GetActions(
    const int p1_stack_depth, const int p2_stack_depth,
    const std::vector<std::shared_ptr<PreflopAction>>& history) const {
    std::vector<std::shared_ptr<PreflopAction>> actions;

    if (is_terminal)
        return actions;

    for (const auto& action : history)
        if (action->IsLegal(p1_stack_depth, p2_stack_depth, history))
            actions.push_back(action);

    return actions;
}

Node::Node(const int p1_stack_depth, const int p2_stack_depth,
    const std::vector<std::shared_ptr<PreflopAction>> &history) : history(history) {
    // set is_terminal
    is_terminal = !history.empty() && history.back()->IsTerminal(history);

    // compute available actions
    actions = GetActions(p1_stack_depth, p2_stack_depth, history);

    // zero out all arrays
    const unsigned long num_actions = actions.size();
    regret_sum.resize(num_actions);
    strategy.resize(num_actions);
    for (int a = 0; a < num_actions; ++a)
        strategy[a] = 1.0 / static_cast<double>(num_actions);
    strategy_sum.resize(num_actions);
};

double Node::GetUtility(const std::vector<u32>& deck, const double p1_equity_multiplier) {
    // this is 1 if p1 was second to last, 2 otherwise
    const unsigned long second_to_last = 2 - (history.size() + 1) % 2;
    // compute the amount each player put into the pot
    auto [p1, p2] = Utils::ComputeOutstandingBets(history);
    if (std::dynamic_pointer_cast<Fold>(history.back()))
        // p1 only realizes <p1_equity_multiplier>% of their utility
        return second_to_last == 1 ? p2 * p1_equity_multiplier : p1;

    const std::vector p1_cards = {deck[0], deck[1], deck[4], deck[5], deck[6], deck[7], deck[8]};
    const std::vector p2_cards = {deck[2], deck[3], deck[4], deck[5], deck[6], deck[7], deck[8]};
    Eval eval;
    const int p1_rank = eval.GetBestHand(p1_cards);
    const int p2_rank = eval.GetBestHand(p2_cards);

    double showdown_multiplier;
    if (p1_rank < p2_rank)      showdown_multiplier = 1;
    else if (p1_rank > p2_rank) showdown_multiplier = -1;
    else                        return 0;

    double position_multiplier = second_to_last == 1 && showdown_multiplier > 0
                                    ? p1_equity_multiplier
                                    : 1;

    return (second_to_last == 1 ? p2 : p1) * showdown_multiplier * position_multiplier;
}

std::vector<double> Node::GetStrategy(const double p) {
    const unsigned long num_actions = actions.size();
    double norm = 0;
    for (int a = 0; a < num_actions; a++) {
        strategy[a] = fmax(regret_sum[a], 0.0);
        norm += strategy[a];
    }
    for (int a = 0; a < num_actions; a++) {
        if (norm > 0)
            strategy[a] /= norm;
        else
            strategy[a] = 1.0 / static_cast<double>(num_actions);
        strategy_sum[a] += p * strategy[a];
    }
    return strategy;
}

void Node::UpdateRegret(const int a, const double v) {
    regret_sum[a] += v;
}

std::vector<double> Node::GetAverageStrategy() const {
    const unsigned long num_actions = actions.size();
    std::vector<double> average_strategy(num_actions);
    double norm = 0;
    for (int a = 0; a < num_actions; ++a)
        norm += strategy_sum[a];
    for (int a = 0; a < num_actions; ++a) {
        if (norm > 0)
        average_strategy[a] = strategy_sum[a] / norm;
        else
        average_strategy[a] = 1.0 / static_cast<double>(num_actions);
    }
    return average_strategy;
}
