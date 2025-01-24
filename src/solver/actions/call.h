//
// Created by Marvin Gandhi on 1/18/25.
//

#ifndef CALL_H
#define CALL_H

#include "action.h"
#include "solver/game_state/game_state.h"

class Call : public Action {
public:
    Call() = default;
    ~Call() override = default;

    /**
     * Calls are only legal if there is a
     * previous aggresive action.
     *
     * @param state The current state of the game.
     * @return true if legal
     */
    [[nodiscard]] bool IsLegal(std::unique_ptr<GameState> state) override;

    /**
     * Calling requiring matching total
     * bets for that street.
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

#endif // CALL_H


