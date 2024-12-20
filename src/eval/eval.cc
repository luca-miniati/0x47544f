#include "eval.h"
#include <iostream>
#include <bit>
#include <string>
#include <stdexcept>

namespace Eval {
    std::array<int, TABLE_SIZE> flushes = {};
    std::array<int, TABLE_SIZE> straights_and_high_cards = {};
    std::unordered_map<u32, int> primes_to_index;

    // Initialize lookup tables flushes and straights_and_high_cards.
    void InitLookupTables() {
        int contiguous_cnt = 1;
        int non_contiguous_cnt = 1;

        // iterate over bitmasks from best to worst
        for (u32 bitmask = 7936; bitmask >= 31; --bitmask) {
            // only consider distinct cards
            if (std::popcount(bitmask) == 5) {
                // check if the bitmask is a straight
                if (std::bit_width(bitmask) - std::countr_zero(bitmask) == 5) {
                    // handle straight flush
                    flushes[bitmask] = contiguous_cnt;
                    // handle straight
                    straights_and_high_cards[bitmask] = 1599 + contiguous_cnt;
                    ++contiguous_cnt;
                // bitmask is non-contiguous (and not the wheel)
                } else if (bitmask != 4111) {
                    flushes[bitmask] = non_contiguous_cnt + 322;
                    straights_and_high_cards[bitmask] = 6185 + non_contiguous_cnt;
                    ++non_contiguous_cnt;
                }
            }
        }

        // handle the straight flush wheel
        flushes[4111] = 10;
        // handle the non-flush wheel
        straights_and_high_cards[4111] = 1609;
    }

    void InitPrimesToIndex() {
        // quads
        int quads_cnt = 1;
        for (int a = 12; a >= 0; --a) {
        for (int b = 12; b >= 0; --b) {
            if (a == b) continue;
            int p = PRIMES[a];
            int q = PRIMES[b];
            primes_to_index[p * p * p * p * q] = 10 + quads_cnt;
            ++quads_cnt;
        }
        }

        // boats
        int boats_cnt = 1;
        for (int a = 12; a >= 0; --a) {
        for (int b = 12; b >= 0; --b) {
            if (a == b) continue;
            int p = PRIMES[a];
            int q = PRIMES[b];
            primes_to_index[p * p * p * q * q] = 166 + boats_cnt;
            ++boats_cnt;
        }
        }

        // trips
        int trips_cnt = 1;
        for (int a = 12; a >= 0; --a) {
        for (int b = 12; b >= 0; --b) {
        for (int c = b - 1; c >= 0; --c) {
            if (a == b || b == c || a == c) continue;
            int p = PRIMES[a];
            int q = PRIMES[b];
            int r = PRIMES[c];
            primes_to_index[p * p * p * q * r] = 1609 + trips_cnt;
            ++trips_cnt;
        }
        }
        }

        // two pairs
        int two_pairs_cnt = 1;
        for (int a = 12; a >= 0; --a) {
        for (int b = a - 1; b >= 0; --b) {
        for (int c = 12; c >= 0; --c) {
            if (a == b || b == c || a == c) continue;
            int p = PRIMES[a];
            int q = PRIMES[b];
            int r = PRIMES[c];
            primes_to_index[p * p * q * q * r] = 2467 + two_pairs_cnt;
            ++two_pairs_cnt;
        }
        }
        }

        // pairs
        int pairs_cnt = 1;
        for (int a = 12; a >= 0; --a) {
        for (int b = 12; b >= 0; --b) {
        for (int c = b - 1; c >= 0; --c) {
        for (int d = c - 1; d >= 0; --d) {
            if (a == b || a == c || a == d || b == c || b == d || c == d) continue;
            int p = PRIMES[a];
            int q = PRIMES[b];
            int r = PRIMES[c];
            int s = PRIMES[d];
            primes_to_index[p * p * q * r * s] = 3325 + pairs_cnt;
            ++pairs_cnt;
        }
        }
        }
        }
    }

    void Init() {
        InitLookupTables();
        InitPrimesToIndex();
    }

    u32 parse_card(std::string s) {
        std::unordered_map<char, int> char_to_rank_index = {
            {'A', 12}, {'K', 11}, {'Q', 10}, {'J', 9}, {'T', 8}, {'9', 7},
            {'8', 6}, {'7', 5}, {'6', 4}, {'5', 3}, {'4', 2}, {'3', 1}, {'2', 0}
        };
        std::unordered_map<char, int> char_to_suit_index = {
            {'c', 3}, {'d', 2}, {'h', 1}, {'s', 0}
        };

        if (s.length() != 2)
            throw std::invalid_argument("card must be in the form Rs, where R = rank, s = suit");
        if (!char_to_rank_index.count(s[0]))
            throw std::invalid_argument("rank: '" + std::to_string(s[0]) + "' not recognized.");
        if (!char_to_suit_index.count(s[1]))
            throw std::invalid_argument("suit: '" + std::to_string(s[0]) + "' not recognized.");

        u32 card = 0;

        int rank_index = char_to_rank_index[s[0]];
        int suit_index = char_to_suit_index[s[1]];

        // set bit for rank
        card |= (1 << (rank_index + 16));

        // set bits for prime
        card |= PRIMES[rank_index];

        // set bit for suit
        card |= (1 << (suit_index + 12));

        return card;
    }

    void parse_hand(u32 (&cards)[5], std::string h) {
        if (h.length() != 10)
            throw std::invalid_argument("hand must be in the form RsRsRsRs, where R = rank, s = suit");

        for (int i = 0; i < 5; ++i) {
            cards[i] = parse_card(h.substr(2 * i, 2));
        }
    }

    std::string card_to_string(const u32 card) {
        std::unordered_map<int, char> rank_index_to_char = {
            {12, 'A'}, {11, 'K'}, {10, 'Q'}, {9, 'J'}, {8, 'T'}, {7, '9'},
            {6, '8'}, {5, '7'}, {4, '6'}, {3, '5'}, {2, '4'}, {1, '3'}, {0, '2'}
        };
        std::unordered_map<char, int> suit_index_to_char = {
            {3, 'c'}, {2, 'd'}, {1, 'h'}, {0, 's'}
        };

        char rank = rank_index_to_char[std::bit_width(card >> 16) - 1];
        char suit = suit_index_to_char[std::bit_width((card & CARD_SUIT) >> 12) - 1];

        if (!rank || !suit)
            throw std::invalid_argument("invalid card.");

        return std::string(1, rank) + suit;
    }

    int EvaluateHand(const u32 cards[5]) {
        u32 suit = cards[0]
                 & cards[1]
                 & cards[2]
                 & cards[3]
                 & cards[4]
                 & CARD_SUIT;
        u32 bitmask = (cards[0]
                     | cards[1]
                     | cards[2]
                     | cards[3]
                     | cards[4])
                     >> 16;

        // check for flush
        if (suit) {
            return flushes[bitmask];
        }

        // check for straight
        if (straights_and_high_cards[bitmask]) {
            return straights_and_high_cards[bitmask];
        }

        u32 primes = (cards[0] & CARD_PRIME)
                  * (cards[1] & CARD_PRIME)
                  * (cards[2] & CARD_PRIME)
                  * (cards[3] & CARD_PRIME)
                  * (cards[4] & CARD_PRIME);

        return primes_to_index[primes];
    }
}
