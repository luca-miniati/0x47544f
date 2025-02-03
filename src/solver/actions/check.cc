//
// Created by Marvin Gandhi on 1/17/25.
//

#include <string>
#include "check.h"

bool Check::IsLegal(std::unique_ptr<GameState> state) {
    return state->history.back() == '_' ||
        state->history.back() == 'k';
}

double Check::GetBetAmount(std::unique_ptr<GameState> state) {
    return 0.0;
}

std::unique_ptr<GameState> Check::Apply(std::unique_ptr<GameState> state) {
    int streets = 0;
    for (char c : state->history) streets += (c == '_');
    bool is_terminal = (streets == 3);

    return std::make_unique<GameState>(
        state->pot,
        state->stack,
        {0, 0},
        0,
        is_terminal,
        0,
        state->player_to_act ^ 3,
        state->history + ((state->history.back() == '_') ? "k" : "k_")
    );
}
