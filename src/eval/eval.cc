#include "eval.h"
#include <bit>
#include <stdexcept>
#include <unordered_map>

Eval::Eval() : flushes{}, straights_and_high_cards{}, primes_to_index{} {
    InitLookupTables();
    InitPrimeToIndex();
}

void Eval::InitLookupTables() {
    int contiguous_cnt = 1;
    int non_contiguous_cnt = 1;

    for (u32 bitmask = 7936; bitmask >= 31; --bitmask) {
        if (std::popcount(bitmask) == 5) {
            if (std::bit_width(bitmask) - std::countr_zero(bitmask) == 5) {
                flushes[bitmask] = contiguous_cnt;
                straights_and_high_cards[bitmask] = 1599 + contiguous_cnt;
                ++contiguous_cnt;
            } else if (bitmask != 4111) {
                flushes[bitmask] = non_contiguous_cnt + 322;
                straights_and_high_cards[bitmask] = 6185 + non_contiguous_cnt;
                ++non_contiguous_cnt;
            }
        }
    }

    flushes[4111] = 10;
    straights_and_high_cards[4111] = 1609;
}

void Eval::InitPrimeToIndex() {
    int quads_cnt = 1;
    for (int a = 12; a >= 0; --a) {
        for (int b = 12; b >= 0; --b) {
            if (a == b) continue;
            primes_to_index[PRIMES[a] * PRIMES[a] * PRIMES[a] * PRIMES[a] * PRIMES[b]] = 10 + quads_cnt;
            ++quads_cnt;
        }
    }

    int boats_cnt = 1;
    for (int a = 12; a >= 0; --a) {
        for (int b = 12; b >= 0; --b) {
            if (a == b) continue;
            primes_to_index[PRIMES[a] * PRIMES[a] * PRIMES[a] * PRIMES[b] * PRIMES[b]] = 166 + boats_cnt;
            ++boats_cnt;
        }
    }

    int trips_cnt = 1;
    for (int a = 12; a >= 0; --a) {
        for (int b = 12; b >= 0; --b) {
            for (int c = b - 1; c >= 0; --c) {
                if (a == b || b == c || a == c) continue;
                primes_to_index[PRIMES[a] * PRIMES[a] * PRIMES[a] * PRIMES[b] * PRIMES[c]] = 1609 + trips_cnt;
                ++trips_cnt;
            }
        }
    }

    int two_pairs_cnt = 1;
    for (int a = 12; a >= 0; --a) {
        for (int b = a - 1; b >= 0; --b) {
            for (int c = 12; c >= 0; --c) {
                if (a == b || b == c || a == c) continue;
                primes_to_index[PRIMES[a] * PRIMES[a] * PRIMES[b] * PRIMES[b] * PRIMES[c]] = 2467 + two_pairs_cnt;
                ++two_pairs_cnt;
            }
        }
    }

    int pairs_cnt = 1;
    for (int a = 12; a >= 0; --a) {
        for (int b = 12; b >= 0; --b) {
            for (int c = b - 1; c >= 0; --c) {
                for (int d = c - 1; d >= 0; --d) {
                    if (a == b || a == c || a == d || b == c || b == d || c == d) continue;
                    primes_to_index[PRIMES[a] * PRIMES[a] * PRIMES[b] * PRIMES[c] * PRIMES[d]] = 3325 + pairs_cnt;
                    ++pairs_cnt;
                }
            }
        }
    }
}

u32 Eval::ParseCard(const std::string& s) const {
    static const std::unordered_map<char, int> char_to_rank_index = {
        {'A', 12}, {'K', 11}, {'Q', 10}, {'J', 9}, {'T', 8}, {'9', 7},
        {'8', 6}, {'7', 5}, {'6', 4}, {'5', 3}, {'4', 2}, {'3', 1}, {'2', 0}
    };
    static const std::unordered_map<char, int> char_to_suit_index = {
        {'c', 3}, {'d', 2}, {'h', 1}, {'s', 0}
    };

    if (s.length() != 2)
        throw std::invalid_argument("card must be in the form Rs, where R = rank, s = suit");
    if (!char_to_rank_index.count(s[0]))
        throw std::invalid_argument("invalid rank");
    if (!char_to_suit_index.count(s[1]))
        throw std::invalid_argument("invalid suit");

    u32 card = 0;
    int rank_index = char_to_rank_index.at(s[0]);
    int suit_index = char_to_suit_index.at(s[1]);

    card |= (1 << (rank_index + 16));
    card |= PRIMES[rank_index];
    card |= (1 << (suit_index + 12));

    return card;
}

std::vector<u32> Eval::ParseHand(const std::string& h) const {
    std::vector<u32> cards(5);

    if (h.length() != 10)
        throw std::invalid_argument("hand must be in the form RsRsRsRsRs, where R = rank, s = suit");

    for (int i = 0; i < 5; ++i) {
        cards[i] = ParseCard(h.substr(2 * i, 2));
    }

    return cards;
}

std::string Eval::CardToString(u32 card) const {
    static const std::unordered_map<int, char> rank_index_to_char = {
        {12, 'A'}, {11, 'K'}, {10, 'Q'}, {9, 'J'}, {8, 'T'}, {7, '9'},
        {6, '8'}, {5, '7'}, {4, '6'}, {3, '5'}, {2, '4'}, {1, '3'}, {0, '2'}
    };
    static const std::unordered_map<int, char> suit_index_to_char = {
        {3, 'c'}, {2, 'd'}, {1, 'h'}, {0, 's'}
    };

    int rank_index = std::bit_width(card >> 16) - 1;
    int suit_index = std::bit_width((card & CARD_SUIT) >> 12) - 1;

    if (!rank_index_to_char.count(rank_index) || !suit_index_to_char.count(suit_index))
        throw std::invalid_argument("invalid card");

    return std::string(1, rank_index_to_char.at(rank_index)) + suit_index_to_char.at(suit_index);
}

int Eval::EvaluateHand(const std::vector<u32>& cards) {
    u32 suit = cards[0] & cards[1] & cards[2] & cards[3] & cards[4] & CARD_SUIT;
    u32 bitmask = (cards[0] | cards[1] | cards[2] | cards[3] | cards[4]) >> 16;

    if (suit)
        return flushes[bitmask];
    if (straights_and_high_cards[bitmask])
        return straights_and_high_cards[bitmask];

    u32 primes = (cards[0] & CARD_PRIME) * (cards[1] & CARD_PRIME) * (cards[2] & CARD_PRIME) *
                 (cards[3] & CARD_PRIME) * (cards[4] & CARD_PRIME);

    return primes_to_index[primes];
}
