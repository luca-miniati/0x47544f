//
// Created by luca miniati on 12/24/24.
//

#ifndef SOLVER_H
#define SOLVER_H
#include <vector>
#include "preflop_action/preflop_action.h"
#include "range/range.h"

/**
 * Represents a GTO preflop solver for No-Limit Texas Hold'Em. A PreflopSolver can train for a set
 * number of iterations, and can return the solution as a Range object. Only heads-up is supported.
 */
class PreflopSolver {
	int p1_stack_depth, p2_stack_depth;
	int num_max_raises;
	double p1_equity_multiplier;
	std::vector<std::shared_ptr<PreflopAction>> p1_action_space, p2_action_space;
public:
	/**
	 * Constructor for PreflopSolver.
	 * @param p1_stack_depth starting stack depth for player 1, in chips
	 * @param p2_stack_depth starting stack depth for player 1, in chips
	 * @param num_max_raises maximum number of raises that can happen preflop. e.g. if
	 *                       num_max_raises = 4, then a 4-bet cannot be 5-bet over the top
	 * @param p1_equity_multiplier number between 0 and 1, representing the proportion of equity
	 *                              that player 1 (the Out-of-Position player) is expected to
	 *                              realize
	 * @param p1_action_space array of PreflopAction's defining the action space for player 1
	 * @param p2_action_space array of PreflopAction's defining the action space for player 2
	 */
	PreflopSolver(int p1_stack_depth, int p2_stack_depth, int num_max_raises,
	              double p1_equity_multiplier,
	              std::vector<std::shared_ptr<PreflopAction>> p1_action_space,
	              std::vector<std::shared_ptr<PreflopAction>> p2_action_space);

	/**
	 * Train the solver for a given number of iterations.
	 * @param num_iterations the number of iterations to train the solver
	 * @param output whether to output training logs
	 */
	void train(int num_iterations, bool output = false);

	/**
	 * Returns the solution.
	 * @return a Range object representing the current strategy of the solver
	 */
	[[nodiscard]] Range get_range(int player) const;
};



#endif //SOLVER_H
