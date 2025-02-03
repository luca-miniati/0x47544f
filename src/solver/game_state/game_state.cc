//
// Created by luca miniati on 1/17/25.
//

#include "game_state.h"
#include <format>

GameState::GameState(std::pair<double, double> pot,
                     std::pair<double, double> stack,
                     std::pair<double, double> bets,
                     const double last_raise,
                     const bool is_terminal,
                     const int num_raises,
                     const int player_to_act,
                     std::string history)
    : pot(std::move(pot)), stack(stack), bets(std::move(bets)), last_raise(last_raise), is_terminal(is_terminal),
      num_raises(num_raises), player_to_act(player_to_act), history(std::move(history)) {
}

std::string GameState::ToString() const {
    return std::format("({}, {})|({}, {})|({}, {})|{}|{}|{}|P{}|{}",
        pot.first,
        pot.second,
        stack.first,
        stack.second,
        bets.first,
        bets.second,
        last_raise,
        is_terminal ? "true" : "false",
        num_raises,
        player_to_act,
        history
    );
}
