//
// Created by luca miniati on 12/26/24.
//

#include "game_state.h"

GameState::GameState(const int player_to_move,
                     const int p1_position,
                     const int p2_position,
                     const double p1_stack_depth,
                     const double p2_stack_depth,
                     const double last_raise,
                     const std::pair<double, double> pot,
                     const bool is_terminal,
                     const bool can_raise,
                     std::vector<std::shared_ptr<PreflopAction> > history,
                     const int max_num_raises) : player_to_move(player_to_move),
                                                 p1_position(p1_position),
                                                 p2_position(p2_position),
                                                 p1_stack_depth(p1_stack_depth),
                                                 p2_stack_depth(p2_stack_depth),
                                                 last_raise(last_raise), pot(pot),
                                                 is_terminal(is_terminal), can_raise(can_raise),
                                                 history(std::move(history)),
                                                 max_num_raises(max_num_raises) {}

GameState GameState::New(const int p1_position, const int p2_position, const double p1_stack_depth,
                         const double p2_stack_depth, const int max_num_raises) {
    return {
        p1_position, p1_position, p2_position, p1_stack_depth, p2_stack_depth, 1, {0, 0}, false, {},
        max_num_raises
    };
}

double GameState::GetChipsRemaining(const int player) const {
    return player == 1 ? p1_stack_depth : p2_stack_depth;
}

std::vector<std::shared_ptr<PreflopAction> > GameState::NextHistory(
    std::shared_ptr<PreflopAction> action) const {
    std::vector<std::shared_ptr<PreflopAction> > next_history = this->history;
    next_history.emplace_back(std::move(action));
    return next_history;
}

int GameState::NextPlayer() const {
    return player_to_move == p1_position ? p1_position : p2_position;
}
