#ifndef EVAL_H
#define EVAL_H

#include <cstdint>
#include <array>
#include <unordered_map>

using u32 = uint32_t;

namespace Eval {
    constexpr size_t TABLE_SIZE = 7937;
    constexpr u32 CARD_BITMASK = 536805376;
    constexpr u32 CARD_SUIT = 61440;
    constexpr u32 CARD_RANK = 3840;
    constexpr u32 CARD_PRIME = 63;
    constexpr std::array<int, 13> PRIMES = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41};

    extern std::array<int, TABLE_SIZE> flushes;
    extern std::array<int, TABLE_SIZE> straights_and_high_cards;
    extern std::unordered_map<u32, int> primes_to_index;

    void InitLookupTables();
    void InitPrimeToIndex();
    void Init();
    u32 parse_card(const std::string s);
    int EvaluateHand(const u32 cards[5]);
}

#endif
