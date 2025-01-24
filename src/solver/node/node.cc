#include "solver/eval/eval.h"
#include "solver/preflop/preflop_action/preflop_action.h"
#include "node.h"

Node::Node(std::shared_ptr<GameState> state, const double p1_equity_multiplier,
           const std::vector<std::shared_ptr<PreflopAction> > &action_space)
    : state(std::move(state)) {
    // compute available actions
    actions = GetActions(action_space);

    // get total bets of each player
    auto [bet1, bet2] = state->GetTotalBets();
    p1_bet = bet1, p2_bet = bet2;
    this->p1_equity_multiplier = p1_equity_multiplier;

    // zero out all arrays
    const unsigned long num_actions = actions.size();
    regret_sum.resize(num_actions);
    strategy.resize(num_actions);
    for (int a = 0; a < num_actions; ++a)
        strategy[a] = 1.0 / static_cast<double>(num_actions);
    strategy_sum.resize(num_actions);
}

std::vector<std::shared_ptr<PreflopAction> > Node::GetActions(
    const std::vector<std::shared_ptr<PreflopAction> > &action_space) const {
    std::vector<std::shared_ptr<PreflopAction> > actions;

    if (state->IsTerminal())
        return actions;

    for (const auto &action: action_space)
        if (action->IsLegal(*state))
            actions.push_back(action);

    return actions;
}

double Node::GetUtility(const std::vector<u32> &deck) const {
    // compute the amount each player put into the pot
    if (std::dynamic_pointer_cast<Fold>(state->history.back()))
        // p1 only realizes <p1_equity_multiplier>% of their utility
        return state->player_to_move == 1 ? p2_bet * p1_equity_multiplier : p1_bet;

    const std::vector p1_cards = {deck[0], deck[1], deck[4], deck[5], deck[6], deck[7], deck[8]};
    const std::vector p2_cards = {deck[2], deck[3], deck[4], deck[5], deck[6], deck[7], deck[8]};
    Eval eval;
    const int p1_rank = eval.GetBestHand(p1_cards);
    const int p2_rank = eval.GetBestHand(p2_cards);

    double showdown_multiplier;
    if (p1_rank < p2_rank) showdown_multiplier = 1;
    else if (p1_rank > p2_rank) showdown_multiplier = -1;
    else return 0;

    const double position_multiplier = state->player_to_move == 1 && showdown_multiplier > 0
                                           ? p1_equity_multiplier
                                           : 1;

    return (state->player_to_move == 1
                ? p2_bet
                : p1_bet) * showdown_multiplier * position_multiplier;
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
