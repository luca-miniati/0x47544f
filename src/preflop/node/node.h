#ifndef NODE_H
#define NODE_H

#include "../../eval/eval.h"
#include "../tree.h"
#include <string>
#include <algorithm>

class Node {
private:
    std::vector<ACTIONS> h;
public:
    int get_utility(std::vector<u32>& deck) {

        bool ip = (h.size() % 2 == 0);

        std::vector<u32> oop_cards = {deck[0], deck[2], deck[5], deck[6], deck[7], deck[9], deck[11]};
        std::vector<u32> ip_cards = {deck[1], deck[3], deck[5], deck[6], deck[7], deck[9], deck[11]};

        Eval eval;

        auto best_hand = [&](const std::vector<u32>& player_cards) {
            int best = INT_MAX;

            for (int i = 0; i < 7; ++i) {
                for (int j = i + 1; j < 7; ++j) {
                    for (int k = j + 1; k < 7; ++k) {
                        for (int l = k + 1; l < 7; ++l) {
                            for (int m = l + 1; m < 7; ++m) {
                                std::vector<u32> cards = {player_cards[i], player_cards[j], player_cards[k], player_cards[l], player_cards[m]};
                                best = std::min(best, eval.EvaluateHand(cards));
                            }
                        }
                    }
                }
            }

            return best;
        };

        int oop_rank = best_hand(oop_cards);
        int ip_rank = best_hand(ip_cards);

        int result;
        if (oop_rank < ip_rank)
            result = 1;
        else if (oop_rank > ip_rank)
            result = -1;
        else
            result = 0;


        double SB = 0.5;
        double BB = 1.0;
        double pot = SB + BB;
        double curr_bet = BB;
        double last_bet = BB;
        bool is_oop = true;

        double hero_in = 0.0;
        bool hero_is_ip = ip;

        for (const auto& action : h) {
            if (is_oop == !hero_is_ip) {
                switch (action) {
                    case CHECK:
                        break;
                    case CALL:
                        hero_in += curr_bet;
                        pot += curr_bet;
                        break;
                    case FOLD:
                        break;
                    case X2:
                        curr_bet *= 2;
                        hero_in += curr_bet;
                        pot += curr_bet;
                        last_bet = curr_bet;
                        break;
                    case X3:
                        curr_bet *= 3;
                        hero_in += curr_bet;
                        pot += curr_bet;
                        last_bet = curr_bet;
                        break;
                    case ALL_IN:
                        // TODO
                        break;
                }
            } else {
                switch (action) {
                    case CHECK:
                        break;
                    case CALL:
                        pot += curr_bet;
                        break;
                    case FOLD:
                        break;
                    case X2:
                        curr_bet *= 2;
                        pot += curr_bet;
                        last_bet = curr_bet;
                        break;
                    case X3:
                        curr_bet *= 3;
                        pot += curr_bet;
                        last_bet = curr_bet;
                        break;
                    case ALL_IN:
                        // TODO
                        break;
                }
            }
            is_oop = !is_oop;
        }

        double util = 0.0;
        if (result == 0) {
            util = 0;
        } else if (result == 1) {
            if (ip) {
                util = -hero_in;
            } else {
                util = pot - hero_in;
            }
        } else {
            if (ip) {
                util = pot - hero_in;
            } else {
                util = -hero_in;
            }
        }

        return util;
    }
};

#endif
