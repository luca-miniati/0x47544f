//
// Created by luca miniati on 12/24/24.
//

// EDIT | Added stubs for a few of the functions we need to implement

#include "preflop_solver.h"
#include <random>
#include <algorithm>
#include "solver/utils/utils.h"

PreFlopSolver::PreFlopSolver(double p1_starting_stack_depth, double p2_starting_stack_depth,
                            int p1_position, int p2_position, int num_max_raises,
                            double p1_equity_multiplier,
                            std::vector<std::shared_ptr<PreFlopSolver>> p1_action_space,
                            std::vector<std::shared_ptr<PreFlopSolver>> p2_action_space)
    : p1_starting_stack_depth(p1_starting_stack_depth),
      p2_starting_stack_depth(p2_starting_stack_depth),
      p1_position(p1_position),
      p2_position(p2_position),
      num_max_raises(num_max_raises),
      p1_equity_multiplier(p1_equity_multiplier),
      p1_action_space(std::move(p1_action_space)),
      p2_action_space(std::move(p2_action_space)) {}

std::shared_ptr<Node> PreFlopSolver::GetNode(u32 c1, u32 c2,
    const std::vector<std::shared_ptr<PreflopAction>>& history) {
    return nullptr;
}

double PreFlopSolver::CFR(std::vector<u32>& deck, std::shared_ptr<GameState> state, double p1, double p2) {
    // base case
    if (state -> IsTerminal()) {
        return 0.0;
    }

    // get current node
    auto node = GetNode(deck[0], deck[1], state -> history);

    // get the current player
    int current_player = state -> player_to_move;

    // get the current strategy
    std::vector<double> strategy = node->GetStrategy(current_player == 1 ? p1 : p2);

    // set up the utility
    std::vector<double> util(strategy.size(), 0.0);
    double node_util = 0.0;

    // go over over each possible action
    // for (size_t a = 0; a < strategy.size(); ++a) {
    // }

    // update regrets
    for (size_t a = 0; a < strategy.size(); ++a) {
        double regret = util[a] - node_util;
        node -> UpdateRegret(a, (current_player == 1 ? p1 : p2) * regret);
    }

    return node_util;
}

void PreFlopSolver::  Train(int num_iterations, bool output) {
    // get a deck of cards
    std::vector<u32> deck = Utils::MakeDeck();

    for (int i = 0; i < num_iterations; ++i) {
        // shuffle the deck
        Utils::Shuffle(deck);
        
        // start with initial game state
        auto state = std::make_shared<GameState>();
        
        // run the CFR-algorithm
        CFR(deck, state, 1.0, 1.0);
    }
}

// Range PreFlopSolver::GetRange(int player) const {
    // TODO: Implement range calculation
    // return Range();
// }
