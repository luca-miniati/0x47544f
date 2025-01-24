#ifndef NODE_H
#define NODE_H

#include "solver/eval/eval.h"
#include "../utils/preflop_solver.h"

// Node in NLHE
class Node {
    std::shared_ptr<GameState> state;
    std::vector<double> strategy, strategy_sum, regret_sum;

    double p1_bet, p2_bet, p1_equity_multiplier;

    // Actions available in this state
    std::vector<std::shared_ptr<PreflopAction> > actions;

    /**
     * Given a history of actions, return the actions that can be taken in this state
     * @return array of legal actions that can be played at this node
     */
    [[nodiscard]] std::vector<std::shared_ptr<PreflopAction> > GetActions(
        const std::vector<std::shared_ptr<PreflopAction> >& action_space) const;

public:
    Node(std::shared_ptr<GameState> state, double p1_equity_multiplier,
         const std::vector<std::shared_ptr<PreflopAction> >& action_space);

    // If this node is terminal, return utility of
    // this node to second-to-last player to act
    [[nodiscard]] double GetUtility(const std::vector<u32> &deck) const;

    // Update strategy using regret matching, using p as the reach probability
    // of being in this state
    std::vector<double> GetStrategy(double p);

    // Update regret value
    void UpdateRegret(int a, double v);

    // Return computed strategy at this node
    [[nodiscard]] std::vector<double> GetAverageStrategy() const;
};

#endif
