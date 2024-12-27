#include <gtest/gtest.h>
#include "solver/eval/eval.h"
#include "solver/utils/utils.h"
#include <vector>

class TestEval : public testing::Test {
protected:
    Eval eval;
};

TEST_F(TestEval, RoyalFlush) {
    std::vector<u32> cards = Utils::ParseCards("AcKcQcJcTc");
    EXPECT_EQ(1, eval.EvaluateHand(cards)) << "WA on AcKcQcJcTc";

    cards = Utils::ParseCards("AdKdQdJdTd");
    EXPECT_EQ(1, eval.EvaluateHand(cards)) << "WA on AdKdQdJdTd";

    cards = Utils::ParseCards("AhKhQhJhTh");
    EXPECT_EQ(1, eval.EvaluateHand(cards)) << "WA on AhKhQhJhTh";

    cards = Utils::ParseCards("AsKsQsJsTs");
    EXPECT_EQ(1, eval.EvaluateHand(cards)) << "WA on AsKsQsJsTs";

    // Regular flush
    cards = Utils::ParseCards("AsKsQsJs9s");
    EXPECT_NE(1, eval.EvaluateHand(cards)) << "WA on AsKsQsJs9s";

    // Straight
    cards = Utils::ParseCards("AsKsQsJsTd");
    EXPECT_NE(1, eval.EvaluateHand(cards)) << "WA on AsKsQsJsTd";

    // Full house
    cards = Utils::ParseCards("AsAhAdJsJd");
    EXPECT_NE(1, eval.EvaluateHand(cards)) << "WA on AsAhAdJsJd";
}

TEST_F(TestEval, StraightFlush) {
    std::vector<u32> cards = Utils::ParseCards("JhTh9h8h7h");
    EXPECT_EQ(4, eval.EvaluateHand(cards)) << "WA on JhTh9h8h7h";

    cards = Utils::ParseCards("6s5s4s3s2s");
    EXPECT_EQ(9, eval.EvaluateHand(cards)) << "WA on 6s5s4s3s2s";
}

TEST_F(TestEval, Quads) {
    std::vector<u32> cards = Utils::ParseCards("AcAdAhAsKd");
    EXPECT_EQ(11, eval.EvaluateHand(cards)) << "WA on AcAdAhAsKd";

    cards = Utils::ParseCards("AcAdAhAsJd");
    EXPECT_EQ(13, eval.EvaluateHand(cards)) << "WA on AcAdAhAsJd";

    cards = Utils::ParseCards("3c3d3h3sKd");
    EXPECT_EQ(144, eval.EvaluateHand(cards)) << "WA on 3c3d3h3sKd";

    cards = Utils::ParseCards("5c5d5h5sJd");
    EXPECT_EQ(122, eval.EvaluateHand(cards)) << "WA on 5c5d5h5sJd";
}

TEST_F(TestEval, FullHouse) {
    std::vector<u32> cards = Utils::ParseCards("JcJdJh5s5s");
    EXPECT_EQ(211, eval.EvaluateHand(cards)) << "WA on JcJdJh5s5s";

    cards = Utils::ParseCards("QcQd2h2s2c");
    EXPECT_EQ(313, eval.EvaluateHand(cards)) << "WA on QcQd2h2s2c";

    cards = Utils::ParseCards("9c9d7h7s9s");
    EXPECT_EQ(233, eval.EvaluateHand(cards)) << "WA on 9c9d7h7s9s";

    cards = Utils::ParseCards("6hAs6dAd6c");
    EXPECT_EQ(263, eval.EvaluateHand(cards)) << "WA on 6hAs6dAd6c";
}

TEST_F(TestEval, Flush) {
    std::vector<u32> cards = Utils::ParseCards("JcTc7c6c5c");
    EXPECT_EQ(1389, eval.EvaluateHand(cards)) << "WA on JcTc7c6c5c";

    cards = Utils::ParseCards("AdKdQd7d2d");
    EXPECT_EQ(356, eval.EvaluateHand(cards)) << "WA on AdKdQd7d2d";

    cards = Utils::ParseCards("9c8c7c6c4c");
    EXPECT_EQ(1548, eval.EvaluateHand(cards)) << "WA on 9c8c7c6c4c";

    cards = Utils::ParseCards("Ah2h3h4h6h");
    EXPECT_EQ(815, eval.EvaluateHand(cards)) << "WA on Ah2h3h4h6h";

    // This is a straight flush
    cards = Utils::ParseCards("Ah2h3h4h5h");
    EXPECT_NE(815, eval.EvaluateHand(cards)) << "WA on Ah2h3h4h5h";
}

TEST_F(TestEval, Straight) {
    std::vector<u32> cards = Utils::ParseCards("JcTc9c8c7h");
    EXPECT_EQ(1603, eval.EvaluateHand(cards)) << "WA on JTc9c8c7h";

    cards = Utils::ParseCards("AdKdQdJcTs");
    EXPECT_EQ(1600, eval.EvaluateHand(cards)) << "WA on AdKdQdJcTs";

    cards = Utils::ParseCards("TsQdAdKdJc");
    EXPECT_EQ(1600, eval.EvaluateHand(cards)) << "WA on TsQdAdKdJc";

    cards = Utils::ParseCards("Ad2h3h4h5c");
    EXPECT_EQ(1609, eval.EvaluateHand(cards)) << "WA on Ad2h3h4h5c";

    // This is a straight flush
    cards = Utils::ParseCards("Ah2h3h4h5h");
    EXPECT_NE(1609, eval.EvaluateHand(cards)) << "WA on Ah2h3h4h5h";
}

TEST_F(TestEval, ThreeOfAKind) {
    std::vector<u32> cards = Utils::ParseCards("JcJdJs8c7h");
    EXPECT_EQ(1853, eval.EvaluateHand(cards)) << "WA on JcJdJs8c7h";

    cards = Utils::ParseCards("AdAhAcQs2h");
    EXPECT_EQ(1630, eval.EvaluateHand(cards)) << "WA on AdAhAcQs2h";

    cards = Utils::ParseCards("4sQd4d4c3s");
    EXPECT_EQ(2298, eval.EvaluateHand(cards)) << "WA on 4sQd4d4c3s";

    cards = Utils::ParseCards("TsTdJdKdTc");
    EXPECT_EQ(1886, eval.EvaluateHand(cards)) << "WA on TsTdJdKdTc";
}

TEST_F(TestEval, TwoPair) {
    std::vector<u32> cards = Utils::ParseCards("JdJh7s7cAd");
    EXPECT_EQ(2864, eval.EvaluateHand(cards)) << "WA on JdJh7s7cAd";

    cards = Utils::ParseCards("2d2s4d4s7h");
    EXPECT_EQ(3311, eval.EvaluateHand(cards)) << "WA on 2d2s4d4s7h";

    cards = Utils::ParseCards("6dKh8cKc6h");
    EXPECT_EQ(2671, eval.EvaluateHand(cards)) << "WA on 6dKh8cKc6h";
}

TEST_F(TestEval, OnePair) {
    std::vector<u32> cards = Utils::ParseCards("2d2h5d4c3c");
    EXPECT_EQ(6185, eval.EvaluateHand(cards)) << "WA on 2d2h5d4c3c";

    cards = Utils::ParseCards("TcAcTh9dKs");
    EXPECT_EQ(4208, eval.EvaluateHand(cards)) << "WA on TcAcTh9dKs";

    cards = Utils::ParseCards("3dTdJs7s3c");
    EXPECT_EQ(5884, eval.EvaluateHand(cards)) << "WA on 3dTdJs7s3c";

    cards = Utils::ParseCards("AdAhKsQcJh");
    EXPECT_EQ(3326, eval.EvaluateHand(cards)) << "WA on AdAhKsQcJh";
}

TEST_F(TestEval, HighCard) {
    std::vector<u32> cards = Utils::ParseCards("7d5c4s3h2d");
    EXPECT_EQ(7462, eval.EvaluateHand(cards)) << "WA on 7d5c4s3h2d";

    cards = Utils::ParseCards("4h5cJh9d7s");
    EXPECT_EQ(7291, eval.EvaluateHand(cards)) << "WA on 4h5cJh9d7s";

    cards = Utils::ParseCards("AdKhQsJc9h");
    EXPECT_EQ(6186, eval.EvaluateHand(cards)) << "WA on AdKhQsJc9h";
}

TEST_F(TestEval, GetBestHand) {
    // Royal flush vs straight flush vs 2 pair
    std::vector<u32> cards = Utils::ParseCards("AcKcQcJcTcAhTd");
    int expected = eval.EvaluateHand(Utils::ParseCards("AcKcQcJcTc"));
    EXPECT_EQ(expected, eval.GetBestHand(cards)) << "WA on GetBestHand royal flush";

    // Straight vs flush
    cards = Utils::ParseCards("AdKdQdJsTd2dQh");
    expected = eval.EvaluateHand(Utils::ParseCards("AdKdQdTd2d"));
    EXPECT_EQ(expected, eval.GetBestHand(cards)) << "WA on GetBestHand flush";

    // Quad vs boat
    cards = Utils::ParseCards("4d4c4h4s3c3h3s");
    expected = eval.EvaluateHand(Utils::ParseCards("4d4c4h4s3h"));
    EXPECT_EQ(expected, eval.GetBestHand(cards)) << "WA on GetBestHand quads";

    // Trips
    cards = Utils::ParseCards("3c3s3dAdKdQdTs");
    expected = eval.EvaluateHand(Utils::ParseCards("3c3s3dAdKd"));
    EXPECT_EQ(expected, eval.GetBestHand(cards)) << "WA on GetBestHand trips";
}