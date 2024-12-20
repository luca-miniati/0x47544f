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
private:
    // Lookup tables and map
    static constexpr size_t TABLE_SIZE = 7937;
    std::array<int, TABLE_SIZE> flushes;
    std::array<int, TABLE_SIZE> straights_and_high_cards;
    std::unordered_map<u32, int> primes_to_index;

public:
    Eval();

    // Takes 5 cards represented as u32's and returns the index of the corresponding
    // hand.
    // e.g. EvaluateHand({ParseCard("Ah"),
    //                    ParseCard("Kh"),
    //                    ParseCard("Qh"),
    //                    ParseCard("Jh"),
    //                    ParseCard("Th")}) = 1, since this is a Royal Flush.
    int EvaluateHand(const std::vector<u32>& cards);

    // Uses EvaluateHand to get the best possible number for 7 cards
    int GetBestHand(const std::vector<u32>& cards);

private:
    // Initialize lookup tables flushes and straights_and_high_cards.
    void InitLookupTables();

    // Initialize lookup map primes_to_index.
    void InitPrimeToIndex();
};

#endif
