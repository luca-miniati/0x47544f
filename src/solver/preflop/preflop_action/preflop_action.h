//
// Created by luca miniati on 12/24/24.
//

#ifndef PREFLOP_ACTION_H
#define PREFLOP_ACTION_H

#include <vector>

class PreflopAction {
	int player;
public:
	explicit PreflopAction(int player);

	virtual ~PreflopAction() = default;

	/**
	 * Gets the player to move.
	 * @return the player who can play this action
	 */
	[[nodiscard]] int GetPlayer() const;

	/**
	 * Given a valid history of PreflopActions, return whether this action can be taken on the next
	 * move.
	 * @param p1_stack_depth starting stack depth for player 1, in chips
	 * @param p2_stack_depth starting stack depth for player 1, in chips
	 * @param history array of valid moves
	 * @return whether this action is a legal move
	 */
	[[nodiscard]] virtual bool IsLegal(int p1_stack_depth, int p2_stack_depth,
	                                   const std::vector<std::shared_ptr<PreflopAction>>& history
	                                   ) const = 0;

	/**
	 * Given a valid history of PreflopActions, return the value of this bet, in big blinds. In
	 * other words, if P is the amount this player has bet in this round of action, and P' is the
	 * amount this player has bet after this action, then return P' - P.
	 * For Checks and Folds, this returns 0.
	 * @param p1_stack_depth starting stack depth for player 1, in chips
	 * @param p2_stack_depth starting stack depth for player 1, in chips
	 * @param history array of valid moves
	 * @return the increase in value that this move induces
	 */
	[[nodiscard]] virtual double GetBetAmount(int p1_stack_depth, int p2_stack_depth,
	                                          const std::vector<std::shared_ptr<PreflopAction>>& history
	                                          ) const = 0;

	static std::shared_ptr<PreflopAction> Fold(int player);
	static std::shared_ptr<PreflopAction> Check(int player);
	static std::shared_ptr<PreflopAction> BetFixed(int player, double bet_amount);
	static std::shared_ptr<PreflopAction> BetMultiple(int player, double bet_multiplier);
	static std::shared_ptr<PreflopAction> BetAllIn(int player);
};

class Fold final : public PreflopAction {
public:
	explicit Fold(int player);

	[[nodiscard]] bool IsLegal(int p1_stack_depth, int p2_stack_depth,
		const std::vector<std::shared_ptr<PreflopAction>>& history) const override;

	[[nodiscard]] double GetBetAmount(int p1_stack_depth, int p2_stack_depth,
		const std::vector<std::shared_ptr<PreflopAction>>& history) const override;
};

class Check final : public PreflopAction {
public:
	explicit Check(int player);

	[[nodiscard]] bool IsLegal(int p1_stack_depth, int p2_stack_depth,
		const std::vector<std::shared_ptr<PreflopAction>>& history) const override;

	[[nodiscard]] double GetBetAmount(int p1_stack_depth, int p2_stack_depth,
		const std::vector<std::shared_ptr<PreflopAction>>& history) const override;
};

class BetFixed final : public PreflopAction {
	int bet_amount;
public:
	explicit BetFixed(int player, int bet_amount);

	[[nodiscard]] bool IsLegal(int p1_stack_depth, int p2_stack_depth,
		const std::vector<std::shared_ptr<PreflopAction>>& history) const override;

	[[nodiscard]] double GetBetAmount(int p1_stack_depth, int p2_stack_depth,
		const std::vector<std::shared_ptr<PreflopAction>>& history) const override;
};

class BetMultiple final : public PreflopAction {
	int bet_multiplier;
public:
	explicit BetMultiple(int player, int bet_multiplier);

	[[nodiscard]] bool IsLegal(int p1_stack_depth, int p2_stack_depth,
		const std::vector<std::shared_ptr<PreflopAction>>& history) const override;

	[[nodiscard]] double GetBetAmount(int p1_stack_depth, int p2_stack_depth,
		const std::vector<std::shared_ptr<PreflopAction>>& history) const override;
};

class BetAllIn final : public PreflopAction {
public:
	explicit BetAllIn(int player);

	[[nodiscard]] bool IsLegal(int p1_stack_depth, int p2_stack_depth,
		const std::vector<std::shared_ptr<PreflopAction>>& history) const override;

	[[nodiscard]] double GetBetAmount(int p1_stack_depth, int p2_stack_depth,
		const std::vector<std::shared_ptr<PreflopAction>>& history) const override;
};

#endif //PREFLOP_ACTION_H
