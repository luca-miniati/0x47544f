//
// Created by Marvin Gandhi on 1/17/25.
//

#ifndef ACTION_H
#define ACTION_H

#include <memory>
#include "solver/game_state/game_state.h" // change to new GS

struct GameAction;

class Action {
public:
    Action();
    virtual ~Action() = default;

    /**
     * Given the pot, bets, last_raise and num_raises from GameState,
     * we determine if the said action is legal.
     *
     * @param state the current state of the game
     * @return true if action is legal, false otherwise
     */
    [[nodiscard]] virtual bool IsLegal(std::unique_ptr<GameState> state) = 0;

    /**
     * Gets the current value staked by our player.
     *
     * @param state the current state of the game
     * @return staked value added to the pot
     */
    [[nodiscard]] virtual double GetBetAmount(std::unique_ptr<GameState> state) = 0;

    /**
     * Returns a new GameState after applying an action to it.
     *
     * @param state the current state of the game
     * @return the updated state of the game
     */
    [[nodiscard]] virtual std::unique_ptr<GameState> Apply(std::unique_ptr<GameState> state) = 0;
};

#endif //ACTION_H
