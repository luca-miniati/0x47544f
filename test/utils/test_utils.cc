#include "../../src/eval/eval.h"
#include "../../src/utils/utils.h"
#include <iostream>
#include <cassert>
#include <stdexcept>
#include <vector>
#include <string>

// Test the utility function parse_card.
void test_parse_card() {
    // Parse cards
    assert((268443689 == Utils::ParseCard("Ah")) && "parse WA on Ah");
    assert((81922 == Utils::ParseCard("2d")) && "parse WA on 2d");
    assert((16810007 == Utils::ParseCard("Tc")) && "parse WA on Tc");
    assert((134221861 == Utils::ParseCard("Ks")) && "parse WA on Ks");
    // check exceptions
    try {
        Utils::ParseCard("Ahh");
        assert(false && "exception not thrown");
    } catch (const std::invalid_argument& e) {
        // should throw this
    } catch (...) {
        assert(false && "wrong exception thrown");
    }
    try {
        Utils::ParseCard("#d");
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
    std::vector<u32> cards = Utils::ParseHand("AcAdAhAsKh");
    std::vector<u32> expected = {
        Utils::ParseCard("Ac"),
        Utils::ParseCard("Ad"),
        Utils::ParseCard("Ah"),
        Utils::ParseCard("As"),
        Utils::ParseCard("Kh")
    };
    assert(expected == cards && "parse WA on AcAdAhAsKh");

    cards = Utils::ParseHand("2d3d4d5d6d");
    expected[0] =  Utils::ParseCard("2d");
    expected[1] = Utils::ParseCard("3d");
    expected[2] = Utils::ParseCard("4d");
    expected[3] = Utils::ParseCard("5d");
    expected[4] = Utils::ParseCard("6d");
    assert(expected == cards && "parse WA on 2d3d4d5d6d");

    // check exceptions
    try {
        Utils::ParseHand("AhKhQhJh");
        assert(false && "exception not thrown");
    } catch (const std::invalid_argument& e) {
        // should throw this
    } catch (...) {
        assert(false && "wrong exception thrown");
    }

    try {
        Utils::ParseHand("AhKhQhJhTh9h");
        assert(false && "exception not thrown");
    } catch (const std::invalid_argument& e) {
        // should throw this
    } catch (...) {
        assert(false && "wrong exception thrown");
    }
    try {
        Utils::ParseHand("AhKhQh?hTh");
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
    assert(("Ac" == Utils::CardToString(Utils::ParseCard("Ac"))) && "card to string WA on Ac");
    assert(("Qd" == Utils::CardToString(Utils::ParseCard("Qd"))) && "card to string WA on Qd");
    assert(("7h" == Utils::CardToString(Utils::ParseCard("7h"))) && "card to string WA on 7h");
    assert(("5s" == Utils::CardToString(Utils::ParseCard("5s"))) && "card to string WA on 5s");

    // check exceptions
    try {
        Utils::CardToString(0);
        assert(false && "exception not thrown");
    } catch (const std::invalid_argument& e) {
        // should throw this
    } catch (...) {
        assert(false && "wrong exception thrown");
    }

    try {
        Utils::CardToString(393216);
        assert(false && "exception not thrown");
    } catch (const std::invalid_argument& e) {
        // should throw this
    } catch (...) {
        assert(false && "wrong exception thrown");
    }
}

// Test utility function make_deck.
void test_make_deck() {
    std::vector<u32> deck = Utils::make_deck();
    std::vector<std::string> deck_strings;
    for (u32 c : deck)
        deck_strings.push_back(Utils::CardToString(c));

    std::vector<std::string> expected = {
        "2c", "3c", "4c", "5c", "6c", "7c", "8c", "9c", "Tc", "Jc", "Qc", "Kc", "Ac",
        "2d", "3d", "4d", "5d", "6d", "7d", "8d", "9d", "Td", "Jd", "Qd", "Kd", "Ad",
        "2h", "3h", "4h", "5h", "6h", "7h", "8h", "9h", "Th", "Jh", "Qh", "Kh", "Ah",
        "2s", "3s", "4s", "5s", "6s", "7s", "8s", "9s", "Ts", "Js", "Qs", "Ks", "As",
    };
    assert(expected == deck_strings && "WA on make_deck");
}

// Test utility function shuffle.
void test_shuffle() {
    std::vector<u32> deck = Utils::make_deck();
    std::vector<u32> shuffled;
    for (u32 c : deck)
        shuffled.push_back(c);

    Utils::shuffle(shuffled);
    // this probably works
    assert(deck != shuffled && "shuffle didn't shuffle");
}

int main() {
    test_parse_card();
    test_parse_hand();
    test_card_to_string();

    test_make_deck();
    test_shuffle();
}
