//
// Created by luca miniati on 1/17/25.
//

#ifndef GAME_STATE_H
#define GAME_STATE_H
#include <string>

/**
 * Represents the state of a game of No-Limit Texas Hold'Em.
 */
struct GameState {
    std::pair<double, double> pot = {0, 0}, stack, bets = {0, 0};
    double last_raise = 0;
    bool is_terminal = false;
    int num_raises = 0;
    int player_to_act;
    std::string history;

    /**
     * Constructor for a new GameState.
     * @param pot a pair of doubles representing the total contributions of each player to the pot,
     *            in big blinds.
     * @param bets a pair of doubles representing the current bets of each player, in big blinds.
     * @param last_raise the last raise made by any player (in big blinds), or 0 if there has been
                         no action. A bet is considered a raise from 0 to <bet_size>.
     * @param is_terminal whether this game state is terminal (equivalently, if we're on the river
     *                    and action is closed.
     * @param num_raises the number of raises that have happened on this street.
     * @param player_to_act the player whose turn it is.
     * @param history a string representation of the actions that have been made.
     */
    GameState(std::pair<double, double> pot, std::pair<double, double> stack, std::pair<double, double> bets,
              double last_raise, bool is_terminal, int num_raises, int player_to_act, std::string history);

    /**
     * Returns a string representation of this game state in the following format:
     *
     * <pot>|<bets>|<last_raise>|<is_terminal>|<num_raises>|<player_to_act>|<history>
     *
     * e.g. "(1, 1)|(2, 0)|2|false|1|P1|b(1.0)" would represent the game state after P1 pots it on the
     *                                     flop in a limped pot.
     */
    [[nodiscard]] std::string ToString() const;
};

#endif //GAME_STATE_H

