//
// Created by luca miniati on 12/24/24.
//

#ifndef PREFLOP_ACTION_H
#define PREFLOP_ACTION_H

#include <vector>

#include "solver/preflop/game_state/game_state.h"

struct GameState;

class PreflopAction {
public:
	explicit PreflopAction();

	virtual ~PreflopAction() = default;

	/**
	 * Given a valid GameState, return whether this action can be taken on the next move.
	 * @param state the current state of the game (not including this action)
	 * @return whether this action is a legal move
	 */
	[[nodiscard]] virtual bool IsLegal(GameState state) = 0;

	/**
	 * Given a valid GameState, return the value of this bet, in big blinds. In other words, if P
	 * is the amount this player has bet in this round of action, and P' is the amount this player
	 * has bet after this action, then return P' - P.
	 * For Checks and Folds, this returns 0.
	 * @param state the current state of the game (not including this action)
	 * @return the increase in value that this move induces
	 */
	[[nodiscard]] virtual double GetBetAmount(GameState state) = 0;

	/**
	 * Returns a hash of this action.
	 * @return a hash of this action
	 */
	[[nodiscard]] virtual std::size_t Hash() const = 0;

	/**
	 * Given a valid GameState, return whether this action, if played on this state, would end the
	 * betting round.
	 * @param state the current state of the game (not including this action)
	 * @return whether this action is terminal
	 */
	[[nodiscard]] virtual bool IsTerminal(GameState state) const = 0;

	/**
	 * Given a valid GameState, return the GameState that follows from playing this action.
	 * @param state the current state of the game (not including this action)
	 * @return a new state representing the state of the game after playing this action.
	 */
	[[nodiscard]] GameState NextState(const GameState &state);

	// Static Factory methods
	static std::shared_ptr<PreflopAction> Fold();
	static std::shared_ptr<PreflopAction> Check();
	static std::shared_ptr<PreflopAction> Call();
	static std::shared_ptr<PreflopAction> Bet(double pot_multiplier);
	static std::shared_ptr<PreflopAction> Raise(double bet_multiplier);
	static std::shared_ptr<PreflopAction> AllIn();
};

class Fold final : public PreflopAction {
public:
	explicit Fold();

	[[nodiscard]] bool IsLegal(GameState state) override;

	[[nodiscard]] double GetBetAmount(GameState state) override;

	[[nodiscard]] std::size_t Hash() const override;

	[[nodiscard]] bool IsTerminal(GameState state) const override;
};

class Check final : public PreflopAction {
public:
	explicit Check();

	[[nodiscard]] bool IsLegal(GameState state) override;

	[[nodiscard]] double GetBetAmount(GameState state) override;

	[[nodiscard]] std::size_t Hash() const override;

	[[nodiscard]] bool IsTerminal(GameState state) const override;
};

class Call final : public PreflopAction {
public:
	explicit Call();

	[[nodiscard]] bool IsLegal(GameState state) override;

	[[nodiscard]] double GetBetAmount(GameState state) override;

	[[nodiscard]] std::size_t Hash() const override;

	[[nodiscard]] bool IsTerminal(GameState state) const override;
};

class Bet final : public PreflopAction {
	double pot_multiplier;
public:
	explicit Bet(double pot_multiplier);

	[[nodiscard]] bool IsLegal(GameState state) override;

	[[nodiscard]] double GetBetAmount(GameState state) override;

	[[nodiscard]] std::size_t Hash() const override;

	[[nodiscard]] bool IsTerminal(GameState state) const override;
};

class Raise final : public PreflopAction {
	double bet_multiplier;
public:
	explicit Raise(double bet_multiplier);

	[[nodiscard]] bool IsLegal(GameState state) override;

	[[nodiscard]] double GetBetAmount(GameState state) override;

	[[nodiscard]] std::size_t Hash() const override;

	[[nodiscard]] bool IsTerminal(GameState state) const override;
};

class AllIn final : public PreflopAction {
public:
	explicit AllIn();

	[[nodiscard]] bool IsLegal(GameState state) override;

	[[nodiscard]] double GetBetAmount(GameState state) override;

	[[nodiscard]] std::size_t Hash() const override;

	[[nodiscard]] bool IsTerminal(GameState state) const override;
};

#endif //PREFLOP_ACTION_H
