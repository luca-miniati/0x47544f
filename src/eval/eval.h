#ifndef EVAL_H
#define EVAL_H

#include <cstdint>
#include <array>
#include <unordered_map>

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
// The table shows the indicies of the hands.
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

// Namespace for NLHE hand evaluation. The main goal of this namespace is to evaluate
// a set of five cards, represented as unsigned 32-bit integers.
//
namespace Eval {
    constexpr size_t TABLE_SIZE = 7937;
    constexpr u32 CARD_BITMASK = 536805376;
    constexpr u32 CARD_SUIT = 61440;
    constexpr u32 CARD_RANK = 3840;
    constexpr u32 CARD_PRIME = 63;
    //                                      2  3  4  5  6   7   8   9   T   J   Q   K   A
    constexpr std::array<int, 13> PRIMES = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41};

    // flushes[b] -> index of flushed hand with bitmask b
    // e.g. if b = 11111, flushes[b] = 9, since b represents a 6-high straight flush
    //
    extern std::array<int, TABLE_SIZE> flushes;
    // straights_and_high_cards[b] -> index of non-flush hand with bitmask b, or 0 if
    //                                the bitmask does not have 5 bits
    // e.g. if b = 101111, straights_and_high_cards[b] = 7462, since b represents the nut low
    //
    extern std::array<int, TABLE_SIZE> straights_and_high_cards;
    // primes_to_index[p] -> index of hand with prime product p
    // e.g. if p = 104553157 = 41^4 * 37, primes_to_index[p] = 11, since p represents the
    // hand AAAAK
    //
    extern std::unordered_map<u32, int> primes_to_index;

    // Initialize lookup tables flushes and straights_and_high_cards.
    //
    void InitLookupTables();

    // Initialize lookup map primes_to_index.
    //
    void InitPrimeToIndex();

    // Initialize lookup tables.
    //
    void Init();

    // string -> card
    // s should be of the form Rs, with R = rank, s = suit.
    //
    u32 parse_card(const std::string s);

    // Populate array of cards with a string of the form RsRsRsRs, with R = rank, s = suit.
    //
    void parse_hand(u32 (&cards)[5], std::string h);

    // card -> string
    // returns string of the form Rs, with R = rank, s = suit.
    //
    std::string card_to_string(const u32 card);

    // Takes 5 cards represented as u32's and returns the index of the corresponding
    // hand.
    // e.g. EvaluateHand({parse_card("Ah"),
    //                    parse_card("Kh"),
    //                    parse_card("Qh"),
    //                    parse_card("Jh"),
    //                    parse_card("Th")}) = 1, since this is a Royal Flush.
    //
    int EvaluateHand(const u32 cards[5]);
}

#endif
