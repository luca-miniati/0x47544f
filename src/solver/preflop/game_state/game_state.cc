//
// Created by luca miniati on 12/26/24.
//

#include "game_state.h"

GameState::GameState(const int player_to_move, const int p1_position, const int p2_position,
                     const double p1_stack_depth, const double p2_stack_depth,
                     std::vector<std::shared_ptr<PreflopAction> > history, const int max_num_raises)
    : player_to_move(player_to_move), max_num_raises(max_num_raises), p1_position(p1_position),
      p2_position(p2_position), p1_stack_depth(p1_stack_depth), p2_stack_depth(p2_stack_depth),
      history(std::move(history)) {
}

bool GameState::IsTerminal() const {
    return !history.empty() && history.back()->IsTerminal(*this);
}

std::pair<double, double> GameState::GetTotalBets() {
    double p1_bet = 0, p2_bet = 0;
    if (p1_position == 0) p1_bet = 0.5;
    else if (p1_position == 1) p1_bet = 1;
    else p1_bet = 0;
    if (p2_position == 0) p2_bet = 0.5;
    else if (p2_position == 1) p2_bet = 1;
    else p2_bet = 0;

    GameState prev_state = GetPreviousGameState();
    for (int i = static_cast<int>(history.size()) - 1; i >= 0; --i) {
        if (player_to_move == 1)
            p1_bet += history[i]->GetBetAmount(prev_state);
        else
            p2_bet += history[i]->GetBetAmount(prev_state);
        prev_state = prev_state.GetPreviousGameState();
    }

    return std::make_pair(p1_bet, p2_bet);
}

bool GameState::CanRaise() const {
    int cnt = 0;
    for (const auto &action: history)
        cnt += action == std::dynamic_pointer_cast<Raise>(action)
                || action == std::dynamic_pointer_cast<Bet>(action);
    return cnt < max_num_raises;
}

double GameState::GetLastRaise() const {
    if (history.empty())
        return 1;

    return abs(pot.first - pot.second);
}

double GameState::GetChipsRemaining(const int player) const {
    return player == 1 ? p1_stack_depth : p2_stack_depth;
}
