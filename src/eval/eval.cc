#include "eval/eval.h"
#include "utils/utils.h"
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
            primes_to_index[Utils::PRIMES[a] * Utils::PRIMES[a] * Utils::PRIMES[a] * Utils::PRIMES[a] * Utils::PRIMES[b]] = 10 + quads_cnt;
            ++quads_cnt;
        }
    }

    int boats_cnt = 1;
    for (int a = 12; a >= 0; --a) {
        for (int b = 12; b >= 0; --b) {
            if (a == b) continue;
            primes_to_index[Utils::PRIMES[a] * Utils::PRIMES[a] * Utils::PRIMES[a] * Utils::PRIMES[b] * Utils::PRIMES[b]] = 166 + boats_cnt;
            ++boats_cnt;
        }
    }

    int trips_cnt = 1;
    for (int a = 12; a >= 0; --a) {
        for (int b = 12; b >= 0; --b) {
            for (int c = b - 1; c >= 0; --c) {
                if (a == b || b == c || a == c) continue;
                primes_to_index[Utils::PRIMES[a] * Utils::PRIMES[a] * Utils::PRIMES[a] * Utils::PRIMES[b] * Utils::PRIMES[c]] = 1609 + trips_cnt;
                ++trips_cnt;
            }
        }
    }

    int two_pairs_cnt = 1;
    for (int a = 12; a >= 0; --a) {
        for (int b = a - 1; b >= 0; --b) {
            for (int c = 12; c >= 0; --c) {
                if (a == b || b == c || a == c) continue;
                primes_to_index[Utils::PRIMES[a] * Utils::PRIMES[a] * Utils::PRIMES[b] * Utils::PRIMES[b] * Utils::PRIMES[c]] = 2467 + two_pairs_cnt;
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
                    primes_to_index[Utils::PRIMES[a] * Utils::PRIMES[a] * Utils::PRIMES[b] * Utils::PRIMES[c] * Utils::PRIMES[d]] = 3325 + pairs_cnt;
                    ++pairs_cnt;
                }
            }
        }
    }
}

int Eval::EvaluateHand(const std::vector<u32>& cards) {
    u32 suit = cards[0] & cards[1] & cards[2] & cards[3] & cards[4] & Utils::CARD_SUIT;
    u32 bitmask = (cards[0] | cards[1] | cards[2] | cards[3] | cards[4]) >> 16;

    if (suit)
        return flushes[bitmask];
    if (straights_and_high_cards[bitmask])
        return straights_and_high_cards[bitmask];

    u32 primes = (cards[0] & Utils::CARD_PRIME) * (cards[1] & Utils::CARD_PRIME) * (cards[2] & Utils::CARD_PRIME) *
                 (cards[3] & Utils::CARD_PRIME) * (cards[4] & Utils::CARD_PRIME);

    return primes_to_index[primes];
}

int Eval::GetBestHand(const std::vector<u32>& cards) {
    int best = INT_MAX;

    for (int i = 0; i < 7; ++i) {
        for (int j = i + 1; j < 7; ++j) {
            for (int k = j + 1; k < 7; ++k) {
                for (int l = k + 1; l < 7; ++l) {
                    for (int m = l + 1; m < 7; ++m) {
                        std::vector<u32> hand = {cards[i], cards[j], cards[k], cards[l], cards[m]};
                        best = std::min(best, EvaluateHand(hand));
                    }
                }
            }
        }
    }

    return best;
}
