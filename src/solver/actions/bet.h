//
// Created by Marvin Gandhi on 1/23/25.
//

#ifndef BET_H
#define BET_H

#include "action.h"
#include "solver/game_state/game_state.h"

class Bet : public Action {
private: double pot_proportion;
public:
    explicit Bet(double pot_proportion) : pot_proportion(pot_proportion) {}
    ~Bet() override = default;

    /**
     * Bets are legal when we are first to act, or
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

#endif // BET_H
