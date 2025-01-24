//
// Created by Marvin Gandhi on 1/17/25.
//

#ifndef FOLD_H
#define FOLD_H

#include "action.h"
#include "solver/game_state/game_state.h"

class Fold : public Action {
public:
    Fold() = default;
    ~Fold() override = default;

    /**
     * Folds are always legal; however, we will not fold if
     * there is no outstanding bet or if the villain checks.
     *
     * @param state The current state of the game.
     * @return true
     */
    [[nodiscard]] bool IsLegal(std::unique_ptr<GameState> state) override;

    /**
     * Folding requires 0 chips.
     *
     * @param state The current state of the game.
     * @return 0
     */
    [[nodiscard]] double GetBetAmount(std::unique_ptr<GameState> state) override;

    /**
     * Updates the history, the player to act, and makes the new GameState terminal.
     *
     * @param state The current state of the game.
     * @return A new GameState reflecting that this player has folded.
     */
    [[nodiscard]] std::unique_ptr<GameState> Apply(std::unique_ptr<GameState> state) override;
};

#endif // FOLD_H
