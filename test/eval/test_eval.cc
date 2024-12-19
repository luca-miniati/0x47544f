#include "../../src/eval/eval.h"
#include <iostream>
#include <cassert>
#include <stdexcept>
#include <vector>

Eval eval;

// Test the utility function parse_card.
void test_parse_card() {
    // Parse cards
    assert((268443689 == eval.ParseCard("Ah")) && "parse WA on Ah");
    assert((81922 == eval.ParseCard("2d")) && "parse WA on 2d");
    assert((16810007 == eval.ParseCard("Tc")) && "parse WA on Tc");
    assert((134221861 == eval.ParseCard("Ks")) && "parse WA on Ks");
    // check exceptions
    try {
        eval.ParseCard("Ahh");
        assert(false && "exception not thrown");
    } catch (const std::invalid_argument& e) {
        // should throw this
    } catch (...) {
        assert(false && "wrong exception thrown");
    }
    try {
        eval.ParseCard("#d");
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
    std::vector<u32> cards = eval.ParseHand("AcAdAhAsKh");
    std::vector<u32> expected = {
        eval.ParseCard("Ac"),
        eval.ParseCard("Ad"),
        eval.ParseCard("Ah"),
        eval.ParseCard("As"),
        eval.ParseCard("Kh")
    };
    assert(expected == cards && "parse WA on AcAdAhAsKh");

    cards = eval.ParseHand("2d3d4d5d6d");
    expected[0] =  eval.ParseCard("2d");
    expected[1] = eval.ParseCard("3d");
    expected[2] = eval.ParseCard("4d");
    expected[3] = eval.ParseCard("5d");
    expected[4] = eval.ParseCard("6d");
    assert(expected == cards && "parse WA on 2d3d4d5d6d");

    // check exceptions
    try {
        eval.ParseHand("AhKhQhJh");
        assert(false && "exception not thrown");
    } catch (const std::invalid_argument& e) {
        // should throw this
    } catch (...) {
        assert(false && "wrong exception thrown");
    }

    try {
        eval.ParseHand("AhKhQhJhTh9h");
        assert(false && "exception not thrown");
    } catch (const std::invalid_argument& e) {
        // should throw this
    } catch (...) {
        assert(false && "wrong exception thrown");
    }
    try {
        eval.ParseHand("AhKhQh?hTh");
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
    assert(("Ac" == eval.CardToString(eval.ParseCard("Ac"))) && "card to string WA on Ac");
    assert(("Qd" == eval.CardToString(eval.ParseCard("Qd"))) && "card to string WA on Qd");
    assert(("7h" == eval.CardToString(eval.ParseCard("7h"))) && "card to string WA on 7h");
    assert(("5s" == eval.CardToString(eval.ParseCard("5s"))) && "card to string WA on 5s");

    // check exceptions
    try {
        eval.CardToString(0);
        assert(false && "exception not thrown");
    } catch (const std::invalid_argument& e) {
        // should throw this
    } catch (...) {
        assert(false && "wrong exception thrown");
    }

    try {
        eval.CardToString(393216);
        assert(false && "exception not thrown");
    } catch (const std::invalid_argument& e) {
        // should throw this
    } catch (...) {
        assert(false && "wrong exception thrown");
    }
}

// Test that royal flushes work.
void test_royal_flush() {
    std::vector<u32> cards = eval.ParseHand("AcKcQcJcTc");
    assert((1 == eval.EvaluateHand(cards)) && "eval WA on AcKcQcJcTc");

    cards = eval.ParseHand("AdKdQdJdTd");
    assert((1 == eval.EvaluateHand(cards)) && "eval WA on AdKdQdJdTd");

    cards = eval.ParseHand("AhKhQhJhTh");
    assert((1 == eval.EvaluateHand(cards)) && "eval WA on AhKhQhJhTh");

    cards = eval.ParseHand("AsKsQsJsTs");
    assert((1 == eval.EvaluateHand(cards)) && "eval WA on AsKsQsJsTs");

    // throw in a regular flush
    cards = eval.ParseHand("AsKsQsJs9s");
    assert((1 != eval.EvaluateHand(cards)) && "eval WA on AsKsQsJs9s");

    // throw in a straight
    cards = eval.ParseHand("AsKsQsJsTd");
    assert((1 != eval.EvaluateHand(cards)) && "eval WA on AsKsQsJsTd");

    // throw in a boat
    cards = eval.ParseHand("AsAhAdJsJd");
    assert((1 != eval.EvaluateHand(cards)) && "eval WA on AsAhAdJsJd");
}

// Test that straight flushes work.
void test_straight_flush() {
    std::vector<u32> cards = eval.ParseHand("JhTh9h8h7h");
    assert((4 == eval.EvaluateHand(cards)) && "eval WA on JhTh9h8h7h");

    cards = eval.ParseHand("6s5s4s3s2s");
    assert((9 == eval.EvaluateHand(cards)) && "eval WA on 6s5s4s3s2s");
}

// Test that quads work.
void test_quads() {
    std::vector<u32> cards = eval.ParseHand("AcAdAhAsKd");
    assert((11 == eval.EvaluateHand(cards)) && "eval WA on AcAdAhAsKd");

    cards = eval.ParseHand("AcAdAhAsJd");
    assert((13 == eval.EvaluateHand(cards)) && "eval WA on AcAdAhAsJd");

    cards = eval.ParseHand("3c3d3h3sKd");
    assert((144 == eval.EvaluateHand(cards)) && "eval WA on 3c3d3h3sKd");

    cards = eval.ParseHand("5c5d5h5sJd");
    assert((122 == eval.EvaluateHand(cards)) && "eval WA on 5c5d5h5sJd");
}

// Test that boats work.
void test_boats() {
    std::vector<u32> cards = eval.ParseHand("JcJdJh5s5s");
    assert((211 == eval.EvaluateHand(cards)) && "eval WA on JcJdJh5s5s");

    cards = eval.ParseHand("QcQd2h2s2c");
    assert((313 == eval.EvaluateHand(cards)) && "eval WA on QcQd2h2s2c");

    cards = eval.ParseHand("9c9d7h7s9s");
    assert((233 == eval.EvaluateHand(cards)) && "eval WA on 9c9d7h7s9s");

    cards = eval.ParseHand("6hAs6dAd6c");
    assert((263 == eval.EvaluateHand(cards)) && "eval WA on 6hAs6dAd6c");
}

// Test that flushes work.
void test_flushes() {
    std::vector<u32> cards = eval.ParseHand("JcTc7c6c5c");
    assert((1389 == eval.EvaluateHand(cards)) && "eval WA on JcTc7c6c5c");

    cards = eval.ParseHand("AdKdQd7d2d");
    assert((356 == eval.EvaluateHand(cards)) && "eval WA on AdKdQd7d2d");

    cards = eval.ParseHand("9c8c7c6c4c");
    assert((1548 == eval.EvaluateHand(cards)) && "eval WA on 9c8c7c6c4c");

    cards = eval.ParseHand("Ah2h3h4h6h");
    assert((815 == eval.EvaluateHand(cards)) && "eval WA on Ah2h3h4h6h");

    // this is a straight flush
    cards = eval.ParseHand("Ah2h3h4h5h");
    assert((815 != eval.EvaluateHand(cards)) && "eval WA on Ah2h3h4h5h");
}

// Test that straigths work.
void test_straights() {
    std::vector<u32> cards = eval.ParseHand("JcTc9c8c7h");
    assert((1603 == eval.EvaluateHand(cards)) && "eval WA on JTc9c8c7h");

    cards = eval.ParseHand("AdKdQdJcTs");
    assert((1600 == eval.EvaluateHand(cards)) && "eval WA on AdKdQdJcTs");

    cards = eval.ParseHand("TsQdAdKdJc");
    assert((1600 == eval.EvaluateHand(cards)) && "eval WA on TsQdAdKdJc");

    cards = eval.ParseHand("Ad2h3h4h5c");
    assert((1609 == eval.EvaluateHand(cards)) && "eval WA on Ad2h3h4h5c");

    // this is a straight flush
    cards = eval.ParseHand("Ah2h3h4h5h");
    assert((1609 != eval.EvaluateHand(cards)) && "eval WA on Ah2h3h4h5h");
}

// Test that trips work.
void test_trips() {
    std::vector<u32> cards = eval.ParseHand("JcJdJs8c7h");
    assert((1853 == eval.EvaluateHand(cards)) && "eval WA on JcJdJs8c7h");

    cards = eval.ParseHand("AdAhAcQs2h");
    assert((1630 == eval.EvaluateHand(cards)) && "eval WA on AdAhAcQs2h");

    cards = eval.ParseHand("4sQd4d4c3s");
    assert((2298 == eval.EvaluateHand(cards)) && "eval WA on 4sQd4d4c3s");

    cards = eval.ParseHand("TsTdJdKdTc");
    assert((1886 == eval.EvaluateHand(cards)) && "eval WA on TsTdJdKdTc");
}

// Test that two pairs work.
void test_two_pairs() {
    std::vector<u32> cards = eval.ParseHand("JdJh7s7cAd");
    assert((2864 == eval.EvaluateHand(cards)) && "eval WA on JdJh7s7cAd");

    cards = eval.ParseHand("2d2s4d4s7h");
    assert((3311 == eval.EvaluateHand(cards)) && "eval WA on 2d2s4d4s7h");

    cards = eval.ParseHand("6dKh8cKc6h");
    assert((2671 == eval.EvaluateHand(cards)) && "eval WA on 6dKh8cKc6h");
}

// Test that pairs work.
void test_pairs() {
    std::vector<u32> cards = eval.ParseHand("2d2h5d4c3c");
    assert((6185 == eval.EvaluateHand(cards)) && "eval WA on 2d2h5d4c3c");

    cards = eval.ParseHand("TcAcTh9dKs");
    assert((4208 == eval.EvaluateHand(cards)) && "eval WA on TcAcTh9dKs");

    cards = eval.ParseHand("3dTdJs7s3c");
    assert((5884 == eval.EvaluateHand(cards)) && "eval WA on 3dTdJs7s3c");

    cards = eval.ParseHand("AdAhKsQcJh");
    assert((3326 == eval.EvaluateHand(cards)) && "eval WA on AdAhKsQcJh");
}

// Test that high cards work.
void test_high_cards() {
    std::vector<u32> cards = eval.ParseHand("7d5c4s3h2d");
    assert((7462 == eval.EvaluateHand(cards)) && "eval WA on 7d5c4s3h2d");

    cards = eval.ParseHand("4h5cJh9d7s");
    assert((7291 == eval.EvaluateHand(cards)) && "eval WA on 4h5cJh9d7s");

    cards = eval.ParseHand("AdKhQsJc9h");
    assert((6186 == eval.EvaluateHand(cards)) && "eval WA on AdKhQsJc9h");
}

int main() {
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
