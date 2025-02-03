//
// Created by Marvin Gandhi on 1/23/25.
//

#ifndef RAISE_H
#define RAISE_H

#include "action.h"
#include "solver/game_state/game_state.h"

class Raise : public Action {
private: double raise_multipler;
public:
    explicit Raise(double raise_multipler) : raise_multipler(raise_multipler) {
        if (raise_multipler <= 1) {
          throw std::invalid_argument("raise_multipler must be greater then 1");
        }
    }
    ~Raise() override = default;

    /**
     * AllIns are always legal unless villan shoves,
     * then we can only call in a heads-up match.
     *s
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

#endif // RAISE_H
