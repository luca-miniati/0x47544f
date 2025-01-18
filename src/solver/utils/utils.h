#ifndef UTILS_H
#define UTILS_H

#include "solver/eval/eval.h"
#include "solver/preflop/preflop_solver.h"

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
	static u32 ParseCard(const std::string &card_string);

	// Populate array of cards with a string of the form RsRsRsRs..., with R = rank, s = suit.
	static std::vector<u32> ParseCards(const std::string &cards_string);

	// card -> string
	// Returns string of the form Rs, with R = rank, s = suit.
	static std::string CardToString(u32 card);

	// Return an unshuffled deck, where the cards are represented by Cactus Kev
	static std::vector<u32> MakeDeck();

	// Shuffle a deck
	static void Shuffle(std::vector<u32> &deck);

	/**
	 * Hash a state consisting of 2 cards and a betting history.
	 * @param c1 player 1's card
	 * @param c2 player 2's card
	 * @param history array of valid moves
	 * @return a hash of this state
	 */
	static std::size_t HashState(u32 c1, u32 c2,
	                             const std::vector<std::shared_ptr<PreflopAction> > &history);

	/**
	 * Helper that mutates `seed` by combining it with `value`.
	 * @param seed the original value
	 * @param value the new value to combine with `seed`
	 */
	static void HashCombine(std::size_t &seed, const std::size_t &value);
};

#endif
