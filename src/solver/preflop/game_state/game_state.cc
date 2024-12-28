//
// Created by luca miniati on 12/26/24.
//
// EDIT | fixed current reasoning and added new methods

#include "game_state.h"
#include <memory>

GameState::GameState(const int player_to_move, const int p1_position, const int p2_position,
                     const double p1_stack_depth, const double p2_stack_depth,
                     std::vector<std::shared_ptr<PreflopAction>> history, const int max_num_raises,
                     const std::pair<double, double>& pot,
                     const double last_raise_amount)
    : player_to_move(player_to_move), max_num_raises(max_num_raises), p1_position(p1_position),
      p2_position(p2_position), p1_stack_depth(p1_stack_depth), p2_stack_depth(p2_stack_depth),
      history(std::move(history)), pot(pot), last_raise_amount(last_raise_amount) {}

bool GameState::IsTerminal() const {
    return !history.empty() && history.back()->IsTerminal(*this);
}

std::pair<double, double> GameState::GetTotalBets() {
    double p1_bet = 0.0, p2_bet = 0.0;
    // determine which player is on turn
    bool is_p1_turn = (player_to_move == 1) ? false : true;

    for (const auto &action : history) {
        if (is_p1_turn) {
            p1_bet += action -> GetBetAmount(*this);
        } else {
            p2_bet += action -> GetBetAmount(*this);
        }
        // change turns
        is_p1_turn = !is_p1_turn;
    }

    return std::make_pair(p1_bet, p2_bet);
}

bool GameState::CanRaise() const {
    int cnt = 0;
    for (const auto &action : history) {
        if (std::dynamic_pointer_cast<Raise>(action) || std::dynamic_pointer_cast<Bet>(action)) {
            cnt++;
        }
    }
    return cnt < max_num_raises;
}

double GameState::GetLastRaise() const {
    return last_raise_amount;
}

double GameState::GetChipsRemaining(const int player) const {
    return player == 1 ? p1_stack_depth : p2_stack_depth;
}

GameState GameState::GetPreviousGameState() const {
    if (history.empty())
        return *this;

    // create a new history vector without the last action
    std::vector<std::shared_ptr<PreflopAction>> prev_history(history.begin(), history.end() - 1);

    // return a new GameState with updated history, pot, and last_raise_amount
    return {player_to_move, p1_position, p2_position, 
            p1_stack_depth, p2_stack_depth, prev_history, max_num_raises, pot, last_raise_amount};
}

GameState GameState::ApplyAction(const std::shared_ptr<PreflopAction>& action) const {
    // copy the current history and add the new action
    std::vector<std::shared_ptr<PreflopAction>> new_history = history;
    new_history.push_back(action);
        
    // calculate new stack depths based on bet amount
    double bet_amount = action -> GetBetAmount(*this);
    double new_p1_stack = p1_stack_depth;
    double new_p2_stack = p2_stack_depth;
    std::pair<double, double> new_pot = pot;

    // reduce bet amount from current player's stack
    if (player_to_move == 1) {
        new_p1_stack -= bet_amount;
        new_pot.first += bet_amount;
    } else {
        new_p2_stack -= bet_amount;
        new_pot.second += bet_amount;
    }

    // update last_raise_amount if the action is a Raise
    double new_last_raise = last_raise_amount;
    if (std::dynamic_pointer_cast<Raise>(action)) {
        new_last_raise = bet_amount;
    }

    // return a new GameState with updated history, stack depths, pot, and last_raise_amount
    // 3 - player_to_move is used to change turns
    return {3 - player_to_move, p1_position, p2_position,
            new_p1_stack, new_p2_stack, new_history, max_num_raises, new_pot, new_last_raise};
}
