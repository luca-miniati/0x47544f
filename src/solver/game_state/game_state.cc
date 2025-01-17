//
// Created by luca miniati on 1/17/25.
//

#include "game_state.h"

GameState::GameState(std::pair<double, double> pot, std::pair<double, double> bets,
                     const double last_raise, const bool is_terminal, const int num_raises,
                     std::string history)
    : pot(std::move(pot)), bets(std::move(bets)), last_raise(last_raise), is_terminal(is_terminal),
      num_raises(num_raises), history(std::move(history)) {
}
