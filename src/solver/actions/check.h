//
// Created by Marvin Gandhi on 1/17/25.
//

#ifndef CHECK_H
#define CHECK_H

#include "action.h"
#include "solver/game_state/game_state.h"

class Check : public Action {
public:
    Check() = default;
    ~Check() override = default;

    /**
     * Checks are legal when we are first to act
     * or there is a check behind us.
     *
     * @param state The current state of the game.
     * @return true if legal
     */
    [[nodiscard]] bool IsLegal(std::unique_ptr<GameState> state) override;

    /**
     * Checking requires 0 chips.
     *
     * @param state The current state of the game.
     * @return 0
     */
    [[nodiscard]] double GetBetAmount(std::unique_ptr<GameState> state) override;

    /**
     * Updates the history and player to act.
     *
     * @param state The current state of the game.
     * @return A new GameState reflecting that this player has folded.
     */
    [[nodiscard]] std::unique_ptr<GameState> Apply(std::unique_ptr<GameState> state) override;
};

#endif // CHECK_H

