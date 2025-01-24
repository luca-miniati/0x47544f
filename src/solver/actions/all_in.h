//
// Created by Marvin Gandhi on 1/19/25.
//

#ifndef ALL_IN_H
#define ALL_IN_H

#include "action.h"
#include "solver/game_state/game_state.h"

class AllIn : public Action {
public:
    AllIn() = default;
    ~AllIn() override = default;
    std::string player;

    /**
     * AllIns are always legal unless villan shoves,
     * then we can only call in a heads-up match.
     *
     * @param state The current state of the game.
     * @return true if legal
     */
    [[nodiscard]] bool IsLegal(std::unique_ptr<GameState> state) override;

    /**
     * AllIn forces our bet amount to be the
     * differnce in the current pot holdings
     * and our stack depth.
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

#endif // ALL_IN_H
