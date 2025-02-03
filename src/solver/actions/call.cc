//
// Created by Marvin Gandhi on 1/18/25.
//

#include "call.h"

bool Call::IsLegal(std::unique_ptr<GameState> state) {
    // call is only legal if a player has a bet out
    return (state->bets.first > 0 || state->bets.second > 0);
}

double Call::GetBetAmount(std::unique_ptr<GameState> state) {
     return std::abs(state->bets.first - state->bets.second);
}

std::unique_ptr<GameState> Call::Apply(std::unique_ptr<GameState> state) {
    int streets = 0;
    for (char c : state->history) streets += (c == '_');
    bool is_terminal = (streets == 3);

    double bet = std::max(state->bets.first, state->bets.second);

    double stack_one = state->stack.first;
    double stack_two = state->stack.second;

    if (state->player_to_act == "P1") {
       stack_one -= bet;
    } else {
       stack_two -= bet;
    }

    return std::make_unique<GameState>(
        {state->pot.first + bet, state->pot.second + bet},
        {stack_one, stack_two}
        {0, 0},
        0,
        is_terminal,
        0,
        state->player_to_act ^ 3,
        state->history + "c_"
    );
}