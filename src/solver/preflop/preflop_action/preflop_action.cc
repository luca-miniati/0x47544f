//
// Created by luca miniati on 12/24/24.
//

#include "preflop_action.h"
#include "../../utils/utils.h"

PreflopAction::PreflopAction() = default;

GameState PreflopAction::NextState(const GameState &state) {
    const double bet_amount = this->GetBetAmount(state);
    double p1_stack_depth = state.p1_stack_depth;
    double p2_stack_depth = state.p2_stack_depth;
    if (state.player_to_move == state.p1_position)
        p1_stack_depth -= bet_amount;
    else
        p2_stack_depth -= bet_amount;
    return {
        state.NextPlayer(), state.p1_position, state.p2_position, p1_stack_depth,
        p2_stack_depth, state.NextHistory(*this), state.max_num_raises
    };
}

Fold::Fold() = default;

Check::Check() = default;

Call::Call() = default;

Bet::Bet(const double pot_multiplier) : pot_multiplier(pot_multiplier) {
}

Raise::Raise(const double bet_multiplier) : bet_multiplier(bet_multiplier) {
}

AllIn::AllIn() = default;

// Static Factory methods
std::shared_ptr<PreflopAction> PreflopAction::Fold() {
    return std::make_shared<::Fold>();
}

std::shared_ptr<PreflopAction> PreflopAction::Check() {
    return std::make_shared<::Check>();
}

std::shared_ptr<PreflopAction> PreflopAction::Call() {
    return std::make_shared<::Call>();
}

std::shared_ptr<PreflopAction> PreflopAction::Bet(double pot_multiplier) {
    return std::make_shared<::Bet>(pot_multiplier);
}

std::shared_ptr<PreflopAction> PreflopAction::Raise(double bet_multiplier) {
    return std::make_shared<::Raise>(bet_multiplier);
}

std::shared_ptr<PreflopAction> PreflopAction::AllIn() {
    return std::make_shared<::AllIn>();
}

// PreflopAction::Fold methods
bool Fold::IsLegal(const GameState state) {
    if (state.is_terminal)
        return false;

    // folding is legal only if there's an outstanding bet to respond to
    auto [p1_bet, p2_bet] = state.pot;

    // players can fold only if the other player has made a higher bet
    return state.player_to_move == 1 ? p2_bet > p1_bet : p1_bet > p2_bet;
}

double Fold::GetBetAmount(const GameState state) {
    // folding does not require any bet
    return 0.0;
}

std::size_t Fold::Hash() const {
    return 1;
}

bool Fold::IsTerminal(const GameState state) const {
    // folding is always terminal
    return true;
}

// PreflopAction::Check methods
bool Check::IsLegal(const GameState state) {
    if (state.is_terminal)
        return false;

    // checking is legal only if there is no outstanding bet to call
    auto [p1_bet, p2_bet] = state.pot;
    return p1_bet == p2_bet;
}

double Check::GetBetAmount(const GameState state) {
    return 0.0;
}

std::size_t Check::Hash() const {
    return 2;
}

bool Check::IsTerminal(const GameState state) const {
    // a check always closes action preflop heads-up
    return true;
}

// PreflopAction::Call methods
bool Call::IsLegal(const GameState state) {
    if (state.is_terminal)
        return false;

    auto [p1_bet, p2_bet] = state.pot;
    // call is legal only if there is an outstanding bet
    return p1_bet != p2_bet;
}

double Call::GetBetAmount(const GameState state) {
    const auto [p1_bet, p2_bet] = state.pot;
    // call amount is always outstanding bet amount
    return abs(p1_bet - p2_bet);
}

std::size_t Call::Hash() const {
    return 3;
}

bool Call::IsTerminal(const GameState state) const {
    // a call always closes action preflop heads-up unless it's p1 limping
    return !state.history.empty();
}

// PreflopAction::Bet methods
bool Bet::IsLegal(const GameState state) {
    if (state.is_terminal || !state.can_raise)
        return false;

    const double chips_remaining = state.GetChipsRemaining(state.player_to_move);
    const double bet_amount = GetBetAmount(state);

    return bet_amount >= 2.0 * state.last_raise // must raise at least 2x
           && bet_amount <= chips_remaining; // must have the chips
}

double Bet::GetBetAmount(const GameState state) {
    // calculate the current pot
    auto [p1_bet, p2_bet] = state.pot;

    // bet is a proportion of the pot
    return (p1_bet + p2_bet) * pot_multiplier;
}

std::size_t Bet::Hash() const {
    std::size_t seed = 4;
    Utils::HashCombine(seed, std::hash<double>{}(pot_multiplier));
    return seed;
}

bool Bet::IsTerminal(const GameState state) const {
    // betting a proportion of the pot never closes action
    return false;
}

// PreflopAction::Raise methods
bool Raise::IsLegal(const GameState state) {
    if (state.is_terminal || !state.can_raise)
        return false;

    const double chips_remaining_1 = state.GetChipsRemaining(1);
    const double chips_remaining_2 = state.GetChipsRemaining(2);

    // this is a legal action if there was a previous bet,
    // and if the raise doesn't put either player all-in (if this is the case, AllIn should be used)
    return state.last_raise > 0
           && std::min(chips_remaining_1, chips_remaining_2) >
           bet_multiplier * state.last_raise;
}

double Raise::GetBetAmount(const GameState state) {
    const double last_raise = state.last_raise;

    // if it's small blind open, they already have 0.5bb in
    if ((state.player_to_move == 1 && state.p1_position == 0)
        || (state.player_to_move == 2 && state.p2_position == 0))
        return last_raise * bet_multiplier - 0.5;
    // if it's big blind open, they already have 1bb in
    if ((state.player_to_move == 1 && state.p1_position == 1)
        || (state.player_to_move == 2 && state.p2_position == 1))
        return last_raise * bet_multiplier - 1;

    // raise is a multiple of the last raise amount
    return last_raise * bet_multiplier;
}

std::size_t Raise::Hash() const {
    std::size_t seed = 5;
    Utils::HashCombine(seed, std::hash<double>{}(bet_multiplier));
    return seed;
}

bool Raise::IsTerminal(const GameState state) const {
    // a raise always re-opens action
    return false;
}

// PreflopAction::AllIn methods
bool AllIn::IsLegal(const GameState state) {
    if (state.is_terminal || state.can_raise)
        return false;

    const double chips_remaining = state.GetChipsRemaining(state.player_to_move);
    return chips_remaining > 0;
}

double AllIn::GetBetAmount(const GameState state) {
    const double chips_remaining_1 = state.GetChipsRemaining(1);
    const double chips_remaining_2 = state.GetChipsRemaining(2);
    // all in always is just the effective stack
    return std::min(chips_remaining_1, chips_remaining_2);
}

std::size_t AllIn::Hash() const {
    return 6;
}

bool AllIn::IsTerminal(const GameState state) const {
    // all-in bet is never terminal (calling an all-in bet would be a Call)
    return false;
}
