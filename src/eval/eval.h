#ifndef EVAL_H
#define EVAL_H

#include <cstdint>
#include <array>
#include <unordered_map>
#include <string>
#include <vector>

// Use Cactus Kev's representation for cards:
//
// +--------+--------+--------+--------+
// |xxxbbbbb|bbbbbbbb|cdhsxxxx|xxpppppp|
// +--------+--------+--------+--------+
// p = prime number of rank (deuce=2,trey=3,four=5,...,ace=41)
// cdhs = suit of card (bit turned on based on suit of card)
// b = bit turned on depending on rank of card
//
using u32 = uint32_t;

// Let a_1, a_2, ..., a_7462 be the sequence of distinct hands in No-Limit Texas
// Hold 'em, ordered by decreasing strength.
//
// The table shows the indices of the hands.
// For example, index 1 corresponds to a Royal Flush. Index 11 corresponds to AAAAK.
//
// +-----------------+-------+------+-------+
// |      Hand       | First | Last | Total |
// +-----------------+-------+------+-------+
// | Straight Flush  |     1 |   10 |    10 |
// | Four of a Kind  |    11 |  166 |   156 |
// | Full House      |   167 |  322 |   156 |
// | Flush           |   323 | 1599 |  1277 |
// | Straight        |  1600 | 1609 |    10 |
// | Three of a Kind |  1610 | 2467 |   858 |
// | Two Pair        |  2468 | 3325 |   858 |
// | Pair            |  3326 | 6185 |  2860 |
// | High Card       |  6186 | 7462 |  1277 |
// +-----------------+-------+------+-------+

class Eval {
public:
    static constexpr size_t TABLE_SIZE = 7937;
    static constexpr u32 CARD_BITMASK = 536805376;
    static constexpr u32 CARD_SUIT = 61440;
    static constexpr u32 CARD_RANK = 3840;
    static constexpr u32 CARD_PRIME = 63;
    //                                             2  3  4  5  6   7   8   9   T   J   Q   K   A
    static constexpr std::array<int, 13> PRIMES = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41};

private:
    // Lookup tables and map
    std::array<int, TABLE_SIZE> flushes;
    std::array<int, TABLE_SIZE> straights_and_high_cards;
    std::unordered_map<u32, int> primes_to_index;

public:
    Eval();

    // Initialize lookup tables flushes and straights_and_high_cards.
    void InitLookupTables();

    // Initialize lookup map primes_to_index.
    void InitPrimeToIndex();

    // string -> card
    // s should be of the form Rs, with R = rank, s = suit.
    u32 ParseCard(const std::string& s) const;

    // Populate array of cards with a string of the form RsRsRsRs, with R = rank, s = suit.
    std::vector<u32> ParseHand(const std::string& h) const;

    // card -> string
    // returns string of the form Rs, with R = rank, s = suit.
    std::string CardToString(u32 card) const;

    // Takes 5 cards represented as u32's and returns the index of the corresponding
    // hand.
    // e.g. EvaluateHand({ParseCard("Ah"),
    //                    ParseCard("Kh"),
    //                    ParseCard("Qh"),
    //                    ParseCard("Jh"),
    //                    ParseCard("Th")}) = 1, since this is a Royal Flush.
    int EvaluateHand(const std::vector<u32>& cards);
};

#endif
