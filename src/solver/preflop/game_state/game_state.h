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
    double p1_stack_depth, p2_stack_depth, last_raise;
    std::pair<double, double> pot;
    bool is_terminal, can_raise;
    std::vector<std::shared_ptr<PreflopAction> > history;

    /**
     * Instantiates an empty history.
     */
    GameState::GameState(int player_to_move, int p1_position, int p2_position,
                         double p1_stack_depth, double p2_stack_depth, double last_raise,
                         std::pair<double, double> pot, bool is_terminal, bool can_raise,
                         std::vector<std::shared_ptr<PreflopAction> > history, int max_num_raises);

    GameState(int p1_position, int p2_position, double p1_stack_depth,
              double p2_stack_depth, std::vector<std::shared_ptr<PreflopAction>> history,
              int max_num_raises);
    /**
     * Instantiates an empty history.
     */
    static GameState GameState::New(int p1_position, int p2_position,
                                    double p1_stack_depth, double p2_stack_depth,
                                    int max_num_raises);

    /**
     * @param player the player whose stack to return
     * @return a double representing the amount of big blinds remaining in `player`'s stack
     */
    [[nodiscard]] double GetChipsRemaining(int player) const;

    /**
     * @return the index of the player position who isn't to move.
     */
    [[nodiscard]] int NextPlayer() const;

    /**
     * @return a copy of `action` appended to `history`.
     */
    [[nodiscard]] std::vector<std::shared_ptr<PreflopAction> >
    NextHistory(std::shared_ptr<PreflopAction> action) const;
};


#endif //GAME_STATE_H
