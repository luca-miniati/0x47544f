#include "solver/eval/eval.h"
#include "solver/utils/utils.h"
#include "solver/preflop/solver.h"
#include <iostream>
#include <random>

u32 Utils::ParseCard(const std::string& s) {
    static const std::unordered_map<char, int> char_to_rank_index = {
        {'A', 12}, {'K', 11}, {'Q', 10}, {'J', 9}, {'T', 8}, {'9', 7},
        {'8', 6}, {'7', 5}, {'6', 4}, {'5', 3}, {'4', 2}, {'3', 1}, {'2', 0}
    };
    static const std::unordered_map<char, int> char_to_suit_index = {
        {'c', 3}, {'d', 2}, {'h', 1}, {'s', 0}
    };

    if (s.length() != 2)
        throw std::invalid_argument("card must be in the form Rs, where R = rank, s = suit");
    if (!char_to_rank_index.contains(s[0]))
        throw std::invalid_argument("invalid rank");
    if (!char_to_suit_index.contains(s[1]))
        throw std::invalid_argument("invalid suit");

    u32 card = 0;
    int rank_index = char_to_rank_index.at(s[0]);
    int suit_index = char_to_suit_index.at(s[1]);

    card |= (1 << (rank_index + 16));
    card |= PRIMES[rank_index];
    card |= (1 << (suit_index + 12));

    return card;
}

std::vector<u32> Utils::ParseCards(const std::string& h) {
    std::vector<u32> cards(h.length() / 2);

    for (int i = 0; i < h.length() / 2; ++i)
        cards[i] = ParseCard(h.substr(2 * i, 2));

    return cards;
}

std::string Utils::CardToString(u32 card) {
    static const std::unordered_map<int, char> rank_index_to_char = {
        {12, 'A'}, {11, 'K'}, {10, 'Q'}, {9, 'J'}, {8, 'T'}, {7, '9'},
        {6, '8'}, {5, '7'}, {4, '6'}, {3, '5'}, {2, '4'}, {1, '3'}, {0, '2'}
    };
    static const std::unordered_map<int, char> suit_index_to_char = {
        {3, 'c'}, {2, 'd'}, {1, 'h'}, {0, 's'}
    };

    const int rank_index = std::bit_width(card >> 16) - 1;
    const int suit_index = std::bit_width((card & CARD_SUIT) >> 12) - 1;

    if (!rank_index_to_char.contains(rank_index) || !suit_index_to_char.contains(suit_index))
        throw std::invalid_argument("invalid card");

    return std::string(1, rank_index_to_char.at(rank_index)) + suit_index_to_char.at(suit_index);
}

std::vector<u32> Utils::MakeDeck() {
    std::vector<u32> deck;
    const std::string ranks = "23456789TJQKA";
    const std::string suits = "cdhs";

    for (int s = 0; s < suits.length(); ++s)
        for (int r = 0; r < ranks.length(); ++r)
            deck.push_back(ParseCard(ranks.substr(r, 1) + suits.substr(s, 1)));

    return deck;
}

void Utils::Shuffle(std::vector<u32>& deck) {
    auto rd = std::random_device();
    auto rng = std::default_random_engine(rd());
    std::ranges::shuffle(deck, rng);
}

std::pair<double, double> Utils::ComputeTotalBets(const std::vector<ACTION> &history) {
    double p1 = 0.5, p2 = 1;

    const unsigned long t = history.size();
    for (int a = 0; a < t; ++a) {
        if (history[a] == CHECK) {
            break;
        }
        if (history[a] == CALL) {
            p1 = std::max(p1, p2);
            p2 = std::max(p1, p2);
        } else if (history[a] == FOLD) {
            break;
        } else if (history[a] == ALL_IN) {
            if (a % 2) p2 = STACK_DEPTH;
            else       p1 = STACK_DEPTH;
        } else if (history[a] == X2) {
            if (a % 2) p2 = 2 * p1;
            else       p1 = 2 * p2;
        } else if (history[a] == X3) {
            if (a % 2) p2 = 3 * p1;
            else       p1 = 3 * p2;
        }
    }

    return {p1, p2};
}

std::size_t Utils::HashState(const u32 c1, const u32 c2, const std::vector<ACTION>& history) {
    std::size_t seed = 0;
    // hash c1 and c2
    std::size_t val = std::hash<u32>{}(c1);
    HashCombine(seed, val);
    val = std::hash<u32>{}(c2);
    HashCombine(seed, val);
    // hash actions
    for (const ACTION action : history) {
        std::size_t element_hash = std::hash<std::underlying_type_t<ACTION>>()(action);
        HashCombine(seed, element_hash);
    }
    return seed;
}

void Utils::HashCombine(std::size_t& seed, std::size_t& value) {
    constexpr std::size_t kMagic = 0x9e3779b97f4a7c16ULL;
    seed ^= value + kMagic + (seed << 6) + (seed >> 2);
}