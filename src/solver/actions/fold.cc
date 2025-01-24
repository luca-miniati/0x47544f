//
// Created by Marvin Gandhi on 1/17/25.
//

#include <string>
#include "fold.h"

bool Fold::IsLegal(std::unique_ptr<GameState> state) {
    return !state->is_terminal && (state->bets.first > 0 || state->bets.second > 0);
}

double Fold::GetBetAmount(std::unique_ptr<GameState> state) {
    return 0.0;
}

std::unique_ptr<GameState> Fold::Apply(std::unique_ptr<GameState> state) {
    return std::make_unique<GameState>(
        state->pot,
        state->stack,
        {0, 0},
        0,
        true,
        0,
        state->player_to_act ^ 3,
        state->history + "f_"
    );
}