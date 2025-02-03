//
// Created by Marvin Gandhi on 1/19/25.
//

#include "all_in.h"

bool AllIn::IsLegal(std::unique_ptr<GameState> state) {
    // allin is only legal if villin hasn't gone all in
    return (state->history.back() != "a");
}

double AllIn::GetBetAmount(std::unique_ptr<GameState> state) {
    return state->player_to_act == "P1" ? std::abs(state->stack.first - state->pot.first)
                       : std::abs(state->stack.second - state->pot.second);
}

std::unique_ptr<GameState> AllIn::Apply(std::unique_ptr<GameState> state) {
    int streets = 0;
    for (char c : state->history) streets += (c == '_');
    bool is_terminal = (streets == 3);

    double pot_one = state->pot.first;
    double pot_two = state->pot.second;
    double stack_one = state->stack.first;
    double stack_two = state->stack.second;

    double a = state->player_to_act == "P1" ? std::abs(state->stack.first - state->pot.first)
                       : std::abs(state->stack.second - state->pot.second);

    // update the pot and stack of the player who goes allin
    if (state->player_to_act == "P1") {
        pot_one = a;
        stack_one = 0;
    } else {
        pot_two = a;
        stack_two = 0;
    }

    return std::make_unique<GameState>(
        {pot_one, pot_two},
        {stack_one, stack_two},
        {0, 0},
        0,
        is_terminal,
        0,
        state->player_to_act ^ 3,
        state->history + ((state->history.back() == '_') ? "a" : "a_")
    );
}