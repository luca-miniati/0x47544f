//
// Created by luca miniati on 12/24/24.
//

// EDIT | Added funtions we need to implement and made style changes

#ifndef SOLVER_H
#define SOLVER_H
#include <vector>
#include "preflop_action/preflop_action.h"
#include "range/range.h"
#include "node/node.h"
/**
 * Represents a GTO preflop solver for No-Limit Texas Hold'Em. A PreFlopSolver can train for a set
 * number of iterations, and can return the solution as a Range object. Only heads-up is supported.
 */
class PreFlopSolver {
    double p1_starting_stack_depth, p2_starting_stack_depth;
    int p1_position, p2_position, num_max_raises;
    double p1_equity_multiplier;
    std::vector<std::shared_ptr<PreFlopSolver> > p1_action_space, p2_action_space;
private:
    std::unordered_map<std::size_t, std::shared_ptr<Node>> tree;
    
    /**
     * Returns a shared pointer to the Node for the current state. 
     * 
     * @param c1 player 1's hole cards
     * @param c2 player 2's hole cards 
     * @param history betting history
     * @return pointer to the node
     */
    std::shared_ptr<Node> GetNode(u32 c1, u32 c2, 
        const std::vector<std::shared_ptr<PreflopAction>>& history);

    /**
     * Runs an iteration of CFR, returning the average game value.
     * 
     * @param deck the current deck state
     * @param state the current game state
     * @param p1 the reach probability for player 1
     * @param p2 the reach probability for player 2
     * @return the expected value for the current player
     */
    double CFR(std::vector<u32>& deck, std::shared_ptr<GameState> state, double p1, double p2);

public:
    /**
     * Constructor for PreFlopSolver.
     * @param p1_starting_stack_depth starting stack depth for player 1, in chips
     * @param p2_starting_stack_depth starting stack depth for player 1, in chips
     * @param p1_position position of player 1, in distance from the small blind
     * @param p2_position position of player 2, in distance from the small blind
     * @param num_max_raises maximum number of raises that can happen preflop. e.g. if
     *                       num_max_raises = 4, then a 4-bet cannot be 5-bet over the top
     * @param p1_equity_multiplier number between 0 and 1, representing the proportion of equity
     *                              that player 1 (the Out-of-Position player) is expected to
     *                              realize
     * @param p1_action_space array of PreFlopSolver's defining the action space for player 1
     * @param p2_action_space array of PreFlopSolver's defining the action space for player 2
     */
    PreFlopSolver(double p1_starting_stack_depth, double p2_starting_stack_depth, int p1_position,
                  int p2_position, int num_max_raises, double p1_equity_multiplier,
                  std::vector<std::shared_ptr<PreFlopSolver> > p1_action_space,
                  std::vector<std::shared_ptr<PreFlopSolver> > p2_action_space);

    /**
     * Train the solver for a given number of iterations.
     * @param num_iterations the number of iterations to train the solver
     * @param output whether to output training logs
     */
    void Train(int num_iterations, bool output = false);

    /**
     * Returns the solution.
     * @param player the player whose strategy to return
     * @return a Range object representing the current strategy of the solver
     */
    [[nodiscard]] Range GetRange(int player) const;
};


#endif //SOLVER_H
