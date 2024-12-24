//
// Created by luca miniati on 12/24/24.
//

#ifndef RANGE_H
#define RANGE_H
#include <unordered_map>

#include "solver/preflop/preflop_action/preflop_action.h"

template<>
struct std::hash<std::shared_ptr<PreflopAction>> {
	std::size_t operator()(const shared_ptr<PreflopAction>& action) const noexcept {
		return action ? action->Hash() : 0;
	}
};

// Represents the solution of a PreflopSolver. For each pair of cards, suited and off-suit, a Range
// defines the frequencies the solution plays.
class Range {
	std::unique_ptr<std::unordered_map<std::string,
	std::unordered_map<std::shared_ptr<PreflopAction>, double>>> frequencies;

public:
	/**
	 * Constructor for Range.
	 * @param frequencies maps hands to strategies, where strategies are maps from actions to
	 *				      proportions
	 */
	explicit Range(std::unique_ptr<std::unordered_map<std::string,
		std::unordered_map<std::shared_ptr<PreflopAction>, double>>> frequencies);

	/**
	 * Returns the frequency at which `hand` plays `action`, or -1 if the move is invalid.
	 * @param action the action to check
	 * @param hand the hand to check, e.g. AA, KTs, 76o
	 * @return the frequency in this range, or -1 if the move is not valid
	 */
	double Get(const std::shared_ptr<PreflopAction> &action, const std::string& hand) const;
};



#endif //RANGE_H
