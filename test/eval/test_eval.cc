#include "../../src/eval/eval.h"
#include <iostream>
#include <cassert>
#include <stdexcept>
#include <vector>

// Test the utility function parse_card.
void test_parse_card() {
    // Parse cards
    assert((268443689 == Eval::parse_card("Ah")) && "parse WA on Ah");
    assert((81922 == Eval::parse_card("2d")) && "parse WA on 2d");
    assert((16810007 == Eval::parse_card("Tc")) && "parse WA on Tc");
    assert((134221861 == Eval::parse_card("Ks")) && "parse WA on Ks");
    // check exceptions
    try {
        Eval::parse_card("Ahh");
        assert(false && "exception not thrown");
    } catch (const std::invalid_argument& e) {
        // should throw this
    } catch (...) {
        assert(false && "wrong exception thrown");
    }
    try {
        Eval::parse_card("#d");
        assert(false && "exception not thrown");
    } catch (const std::invalid_argument& e) {
        // should throw this
    } catch (...) {
        assert(false && "wrong exception thrown");
    }
}

// Test the utility function parse_hand.
void test_parse_hand() {
    // Parse hands
    u32 cards[5];
    Eval::parse_hand(cards, "AcAdAhAsKh");
    u32 expected[5] = {
        Eval::parse_card("Ac"),
        Eval::parse_card("Ad"),
        Eval::parse_card("Ah"),
        Eval::parse_card("As"),
        Eval::parse_card("Kh")
    };
    assert(std::equal(expected, expected + 5, cards) && "parse WA on AcAdAhAsKh");
    Eval::parse_hand(cards, "2d3d4d5d6d");
    expected[0] =  Eval::parse_card("2d");
    expected[1] = Eval::parse_card("3d");
    expected[2] = Eval::parse_card("4d");
    expected[3] = Eval::parse_card("5d");
    expected[4] = Eval::parse_card("6d");
    assert(std::equal(expected, expected + 5, cards) && "parse WA on 2d3d4d5d6d");
    // check exceptions
    try {
        Eval::parse_hand(cards, "AhKhQhJh");
        assert(false && "exception not thrown");
    } catch (const std::invalid_argument& e) {
        // should throw this
    } catch (...) {
        assert(false && "wrong exception thrown");
    }
    try {
        Eval::parse_hand(cards, "AhKhQhJhTh9h");
        assert(false && "exception not thrown");
    } catch (const std::invalid_argument& e) {
        // should throw this
    } catch (...) {
        assert(false && "wrong exception thrown");
    }
    try {
        Eval::parse_hand(cards, "AhKhQh?hTh");
        assert(false && "exception not thrown");
    } catch (const std::invalid_argument& e) {
        // should throw this
    } catch (...) {
        assert(false && "wrong exception thrown");
    }
}

// Test utility function card_to_string.
void test_card_to_string() {
    // Test cards
    assert(("Ac" == Eval::card_to_string(Eval::parse_card("Ac"))) && "card to string WA on Ac");
    assert(("Qd" == Eval::card_to_string(Eval::parse_card("Qd"))) && "card to string WA on Qd");
    assert(("7h" == Eval::card_to_string(Eval::parse_card("7h"))) && "card to string WA on 7h");
    assert(("5s" == Eval::card_to_string(Eval::parse_card("5s"))) && "card to string WA on 5s");
    // check exceptions
    try {
        Eval::card_to_string(0);
        assert(false && "exception not thrown");
    } catch (const std::invalid_argument& e) {
        // should throw this
    } catch (...) {
        assert(false && "wrong exception thrown");
    }
    try {
        Eval::card_to_string(393216);
        assert(false && "exception not thrown");
    } catch (const std::invalid_argument& e) {
        // should throw this
    } catch (...) {
        assert(false && "wrong exception thrown");
    }
}

// Test that royal flushes work.
void test_royal_flush() {
    u32 cards[5];

    Eval::parse_hand(cards, "AcKcQcJcTc");
    assert((1 == Eval::EvaluateHand(cards)) && "eval WA on AcKcQcJcTc");
    Eval::parse_hand(cards, "AdKdQdJdTd");
    assert((1 == Eval::EvaluateHand(cards)) && "eval WA on AdKdQdJdTd");
    Eval::parse_hand(cards, "AhKhQhJhTh");
    assert((1 == Eval::EvaluateHand(cards)) && "eval WA on AhKhQhJhTh");
    Eval::parse_hand(cards, "AsKsQsJsTs");
    assert((1 == Eval::EvaluateHand(cards)) && "eval WA on AsKsQsJsTs");
    // throw in a regular flush
    Eval::parse_hand(cards, "AsKsQsJs9s");
    assert((1 != Eval::EvaluateHand(cards)) && "eval WA on AsKsQsJs9s");
    // throw in a straight
    Eval::parse_hand(cards, "AsKsQsJsTd");
    assert((1 != Eval::EvaluateHand(cards)) && "eval WA on AsKsQsJsTd");
    // throw in a boat
    Eval::parse_hand(cards, "AsAhAdJsJd");
    assert((1 != Eval::EvaluateHand(cards)) && "eval WA on AsAhAdJsJd");
}

// Test that straight flushes work.
void test_straight_flush() {
    u32 cards[5];

    Eval::parse_hand(cards, "JhTh9h8h7h");
    assert((4 == Eval::EvaluateHand(cards)) && "eval WA on JhTh9h8h7h");
    Eval::parse_hand(cards, "6s5s4s3s2s");
    assert((9 == Eval::EvaluateHand(cards)) && "eval WA on 6s5s4s3s2s");
}

// Test that quads work.
void test_quads() {
    u32 cards[5];

    Eval::parse_hand(cards, "AcAdAhAsKd");
    assert((11 == Eval::EvaluateHand(cards)) && "eval WA on AcAdAhAsKd");
    Eval::parse_hand(cards, "AcAdAhAsJd");
    assert((13 == Eval::EvaluateHand(cards)) && "eval WA on AcAdAhAsJd");
    Eval::parse_hand(cards, "3c3d3h3sKd");
    assert((144 == Eval::EvaluateHand(cards)) && "eval WA on 3c3d3h3sKd");
    Eval::parse_hand(cards, "5c5d5h5sJd");
    assert((122 == Eval::EvaluateHand(cards)) && "eval WA on 5c5d5h5sJd");
}

// Test that boats work.
void test_boats() {
    u32 cards[5];

    Eval::parse_hand(cards, "JcJdJh5s5s");
    assert((211 == Eval::EvaluateHand(cards)) && "eval WA on JcJdJh5s5s");
    Eval::parse_hand(cards, "QcQd2h2s2c");
    assert((313 == Eval::EvaluateHand(cards)) && "eval WA on QcQd2h2s2c");
    Eval::parse_hand(cards, "9c9d7h7s9s");
    assert((233 == Eval::EvaluateHand(cards)) && "eval WA on 9c9d7h7s9s");
    Eval::parse_hand(cards, "6hAs6dAd6c");
    assert((263 == Eval::EvaluateHand(cards)) && "eval WA on 6hAs6dAd6c");
}

// Test that flushes work.
void test_flushes() {
    u32 cards[5];

    Eval::parse_hand(cards, "JcTc7c6c5c");
    assert((1389 == Eval::EvaluateHand(cards)) && "eval WA on JcTc7c6c5c");
    Eval::parse_hand(cards, "AdKdQd7d2d");
    assert((356 == Eval::EvaluateHand(cards)) && "eval WA on AdKdQd7d2d");
    Eval::parse_hand(cards, "9c8c7c6c4c");
    assert((1548 == Eval::EvaluateHand(cards)) && "eval WA on 9c8c7c6c4c");
    Eval::parse_hand(cards, "Ah2h3h4h6h");
    assert((815 == Eval::EvaluateHand(cards)) && "eval WA on Ah2h3h4h6h");
    // this is a straight-flush
    Eval::parse_hand(cards, "Ah2h3h4h5h");
    assert((815 != Eval::EvaluateHand(cards)) && "eval WA on Ah2h3h4h5h");
}

// Test that straigths work.
void test_straights() {
    u32 cards[5];

    Eval::parse_hand(cards, "JcTc9c8c7h");
    assert((1603 == Eval::EvaluateHand(cards)) && "eval WA on JTc9c8c7h");
    Eval::parse_hand(cards, "AdKdQdJcTs");
    assert((1600 == Eval::EvaluateHand(cards)) && "eval WA on AdKdQdJcTs");
    Eval::parse_hand(cards, "TsQdAdKdJc");
    assert((1600 == Eval::EvaluateHand(cards)) && "eval WA on TsQdAdKdJc");
    Eval::parse_hand(cards, "Ad2h3h4h5c");
    assert((1609 == Eval::EvaluateHand(cards)) && "eval WA on Ad2h3h4h5c");
    // this is a straight-flush
    Eval::parse_hand(cards, "Ah2h3h4h5h");
    assert((1609 != Eval::EvaluateHand(cards)) && "eval WA on Ah2h3h4h5h");
}

// Test that trips work.
void test_trips() {
    u32 cards[5];

    Eval::parse_hand(cards, "JcJdJs8c7h");
    assert((1853 == Eval::EvaluateHand(cards)) && "eval WA on JcJdJs8c7h");
    Eval::parse_hand(cards, "AdAhAcQs2h");
    assert((1630 == Eval::EvaluateHand(cards)) && "eval WA on AdAhAcQs2h");
    Eval::parse_hand(cards, "TsTdJdKdTc");
    assert((1886 == Eval::EvaluateHand(cards)) && "eval WA on TsTdJdKdTc");
}

// Test that two pairs work.
void test_two_pairs() {
    u32 cards[5];

    Eval::parse_hand(cards, "JdJh7s7cAd");
    assert((2864 == Eval::EvaluateHand(cards)) && "eval WA on JdJh7s7cAd");
    Eval::parse_hand(cards, "2d2s4d4s7h");
    assert((3311 == Eval::EvaluateHand(cards)) && "eval WA on 2d2s4d4s7h");
    Eval::parse_hand(cards, "6dKh8cKc6h");
    assert((2671 == Eval::EvaluateHand(cards)) && "eval WA on 6dKh8cKc6h");
}

// Test that pairs work.
void test_pairs() {
    u32 cards[5];

    // lowest pair
    Eval::parse_hand(cards, "2d2h5d4c3c");
    assert((6185 == Eval::EvaluateHand(cards)) && "eval WA on 2d2h5d4c3c");

    // highest pair
    Eval::parse_hand(cards, "AdAhKsQcJh");
    assert((3326 == Eval::EvaluateHand(cards)) && "eval WA on AdAhKsQcJh");
}

// Test that high cards work.
void test_high_cards() {
    u32 cards[5];

    // lowest high card
    Eval::parse_hand(cards, "7d5c4s3h2d");
    assert((7462 == Eval::EvaluateHand(cards)) && "eval WA on 7d5c4s3h2d");

    // highest high card
    Eval::parse_hand(cards, "AdKhQsJc9h");
    assert((6186 == Eval::EvaluateHand(cards)) && "eval WA on AdKhQsJc9h");
}

int main() {
    Eval::Init();

    test_parse_card();
    test_parse_hand();
    test_card_to_string();
    test_royal_flush();
    test_straight_flush();
    test_quads();
    test_boats();
    test_flushes();
    test_straights();
    test_trips();
    test_two_pairs();
    test_pairs();
    test_high_cards();
}
