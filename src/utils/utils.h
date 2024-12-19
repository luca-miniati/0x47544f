#ifndef UTILS_H
#define UTILS_H

#include "../eval/eval.h"

class Utils {
public:
    static constexpr u32 CARD_BITMASK = 536805376;
    static constexpr u32 CARD_SUIT = 61440;
    static constexpr u32 CARD_RANK = 3840;
    static constexpr u32 CARD_PRIME = 63;
    //                                             2  3  4  5  6   7   8   9   T   J   Q   K   A
    static constexpr std::array<int, 13> PRIMES = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41};

    // string -> card
    // s should be of the form Rs, with R = rank, s = suit.
    static u32 ParseCard(const std::string& s);

    // Populate array of cards with a string of the form RsRsRsRs, with R = rank, s = suit.
    static std::vector<u32> ParseHand(const std::string& h);

    // card -> string
    // returns string of the form Rs, with R = rank, s = suit.
    static std::string CardToString(u32 card);

    // return an unshuffled deck, where the cards are represented by Cactus Kev
    static std::vector<u32> make_deck();

    // shuffle a deck
    static void shuffle(std::vector<u32>& deck);
};

#endif
