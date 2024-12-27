//
// Created by luca miniati on 12/26/24.
//

#ifndef GAME_STATE_H
#define GAME_STATE_H
#include <vector>
#include "solver/preflop/preflop_action/preflop_action.h"

class PreflopAction;

struct GameState {
    int player_to_move, max_num_raises, p1_position, p2_position;
    double p1_stack_depth, p2_stack_depth;
    std::pair<double, double> pot;
    std::vector<std::shared_ptr<PreflopAction> > history;

    GameState(int player_to_move, int p1_position, int p2_position, double p1_stack_depth,
              double p2_stack_depth, std::vector<std::shared_ptr<PreflopAction> > history,
              int max_num_raises);

    /**
     * Return whether this is a terminal state.
     * @return whether this is a terminal state
     */
    [[nodiscard]] bool IsTerminal() const;

    /**
     * Return the total amount each player has contributed to the pot.
     * @return a pair of doubles {p1_contribution, p2_contribution}
     */
    [[nodiscard]] std::pair<double, double> GetTotalBets();

    /**
     * Return the amount of the last raise that happened. If the last action wasn't a raise, this
     * returns 0.
     * @return a double representing the amount of the last raise
     */
    [[nodiscard]] double GetLastRaise() const;

    /**
     * Return whether the next action can be a raise. This can happen only if the current number of
     * raises is less than `max_num_raises`.
     * @return whether the next player can raise
     */
    [[nodiscard]] bool CanRaise() const;

    /**
     * Return the number of big blinds in `player`'s stack.
     * @param player the player whose stack to return
     * @return a double representing the amount of big blinds remaining
     */
    [[nodiscard]] double GetChipsRemaining(int player) const;
};


#endif //GAME_STATE_H
