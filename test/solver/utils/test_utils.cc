#include <gtest/gtest.h>
#include "solver/eval/eval.h"
#include "solver/utils/utils.h"
#include <vector>
#include <string>

class TestUtils : public testing::Test {
};

TEST_F(TestUtils, ParseCard) {
    EXPECT_EQ(268443689, Utils::ParseCard("Ah")) << "parse WA on Ah";
    EXPECT_EQ(81922, Utils::ParseCard("2d")) << "parse WA on 2d";
    EXPECT_EQ(16810007, Utils::ParseCard("Tc")) << "parse WA on Tc";
    EXPECT_EQ(134221861, Utils::ParseCard("Ks")) << "parse WA on Ks";

    // Check exceptions
    EXPECT_THROW(Utils::ParseCard("Ahh"), std::invalid_argument);
    EXPECT_THROW(Utils::ParseCard("#d"), std::invalid_argument);
}

TEST_F(TestUtils, ParseCards) {
    // Parse hands
    std::vector<u32> cards = Utils::ParseCards("AcAdAhAsKh");
    std::vector expected = {
        Utils::ParseCard("Ac"),
        Utils::ParseCard("Ad"),
        Utils::ParseCard("Ah"),
        Utils::ParseCard("As"),
        Utils::ParseCard("Kh")
    };
    EXPECT_EQ(expected, cards) << "parse WA on AcAdAhAsKh";

    cards = Utils::ParseCards("2d3d4d5d6d");
    expected = {
        Utils::ParseCard("2d"),
        Utils::ParseCard("3d"),
        Utils::ParseCard("4d"),
        Utils::ParseCard("5d"),
        Utils::ParseCard("6d")
    };
    EXPECT_EQ(expected, cards) << "parse WA on 2d3d4d5d6d";

    EXPECT_THROW(Utils::ParseCards("AhKhQh?hTh"), std::invalid_argument);
}

TEST_F(TestUtils, CardToString) {
    EXPECT_EQ("Ac", Utils::CardToString(Utils::ParseCard("Ac"))) << "card to string WA on Ac";
    EXPECT_EQ("Qd", Utils::CardToString(Utils::ParseCard("Qd"))) << "card to string WA on Qd";
    EXPECT_EQ("7h", Utils::CardToString(Utils::ParseCard("7h"))) << "card to string WA on 7h";
    EXPECT_EQ("5s", Utils::CardToString(Utils::ParseCard("5s"))) << "card to string WA on 5s";

    // Check exceptions
    EXPECT_THROW(Utils::CardToString(0), std::invalid_argument);
    EXPECT_THROW(Utils::CardToString(393216), std::invalid_argument);
}

TEST_F(TestUtils, MakeDeck) {
    const std::vector<u32> deck = Utils::MakeDeck();
    std::vector<std::string> deck_strings;
    deck_strings.reserve(deck.size());
    for (const u32 c : deck) {
        deck_strings.push_back(Utils::CardToString(c));
    }

    const std::vector<std::string> expected = {
        "2c", "3c", "4c", "5c", "6c", "7c", "8c", "9c", "Tc", "Jc", "Qc", "Kc", "Ac",
        "2d", "3d", "4d", "5d", "6d", "7d", "8d", "9d", "Td", "Jd", "Qd", "Kd", "Ad",
        "2h", "3h", "4h", "5h", "6h", "7h", "8h", "9h", "Th", "Jh", "Qh", "Kh", "Ah",
        "2s", "3s", "4s", "5s", "6s", "7s", "8s", "9s", "Ts", "Js", "Qs", "Ks", "As"
    };
    EXPECT_EQ(expected, deck_strings) << "WA on make_deck";
}

TEST_F(TestUtils, Shuffle) {
    const std::vector<u32> deck = Utils::MakeDeck();
    std::vector shuffled(deck.begin(), deck.end());

    Utils::Shuffle(shuffled);
    EXPECT_NE(deck, shuffled) << "shuffle didn't shuffle";
}