#include "solver/eval/eval.h"
#include "solver/utils/utils.h"
#include <iostream>
#include <cassert>
#include <vector>

Eval eval;

// Test that royal flushes work.
void test_royal_flush() {
    std::vector<u32> cards = Utils::ParseCards("AcKcQcJcTc");
    assert((1 == eval.EvaluateHand(cards)) && "Utils::WA on AcKcQcJcTc");

    cards = Utils::ParseCards("AdKdQdJdTd");
    assert((1 == eval.EvaluateHand(cards)) && "Utils::WA on AdKdQdJdTd");

    cards = Utils::ParseCards("AhKhQhJhTh");
    assert((1 == eval.EvaluateHand(cards)) && "Utils::WA on AhKhQhJhTh");

    cards = Utils::ParseCards("AsKsQsJsTs");
    assert((1 == eval.EvaluateHand(cards)) && "Utils::WA on AsKsQsJsTs");

    // throw in a regular flush
    cards = Utils::ParseCards("AsKsQsJs9s");
    assert((1 != eval.EvaluateHand(cards)) && "Utils::WA on AsKsQsJs9s");

    // throw in a straight
    cards = Utils::ParseCards("AsKsQsJsTd");
    assert((1 != eval.EvaluateHand(cards)) && "Utils::WA on AsKsQsJsTd");

    // throw in a boat
    cards = Utils::ParseCards("AsAhAdJsJd");
    assert((1 != eval.EvaluateHand(cards)) && "Utils::WA on AsAhAdJsJd");
}

// Test that straight flushes work.
void test_straight_flush() {
    std::vector<u32> cards = Utils::ParseCards("JhTh9h8h7h");
    assert((4 == eval.EvaluateHand(cards)) && "Utils::WA on JhTh9h8h7h");

    cards = Utils::ParseCards("6s5s4s3s2s");
    assert((9 == eval.EvaluateHand(cards)) && "Utils::WA on 6s5s4s3s2s");
}

// Test that quads work.
void test_quads() {
    std::vector<u32> cards = Utils::ParseCards("AcAdAhAsKd");
    assert((11 == eval.EvaluateHand(cards)) && "Utils::WA on AcAdAhAsKd");

    cards = Utils::ParseCards("AcAdAhAsJd");
    assert((13 == eval.EvaluateHand(cards)) && "Utils::WA on AcAdAhAsJd");

    cards = Utils::ParseCards("3c3d3h3sKd");
    assert((144 == eval.EvaluateHand(cards)) && "Utils::WA on 3c3d3h3sKd");

    cards = Utils::ParseCards("5c5d5h5sJd");
    assert((122 == eval.EvaluateHand(cards)) && "Utils::WA on 5c5d5h5sJd");
}

// Test that boats work.
void test_boats() {
    std::vector<u32> cards = Utils::ParseCards("JcJdJh5s5s");
    assert((211 == eval.EvaluateHand(cards)) && "Utils::WA on JcJdJh5s5s");

    cards = Utils::ParseCards("QcQd2h2s2c");
    assert((313 == eval.EvaluateHand(cards)) && "Utils::WA on QcQd2h2s2c");

    cards = Utils::ParseCards("9c9d7h7s9s");
    assert((233 == eval.EvaluateHand(cards)) && "Utils::WA on 9c9d7h7s9s");

    cards = Utils::ParseCards("6hAs6dAd6c");
    assert((263 == eval.EvaluateHand(cards)) && "Utils::WA on 6hAs6dAd6c");
}

// Test that flushes work.
void test_flushes() {
    std::vector<u32> cards = Utils::ParseCards("JcTc7c6c5c");
    assert((1389 == eval.EvaluateHand(cards)) && "Utils::WA on JcTc7c6c5c");

    cards = Utils::ParseCards("AdKdQd7d2d");
    assert((356 == eval.EvaluateHand(cards)) && "Utils::WA on AdKdQd7d2d");

    cards = Utils::ParseCards("9c8c7c6c4c");
    assert((1548 == eval.EvaluateHand(cards)) && "Utils::WA on 9c8c7c6c4c");

    cards = Utils::ParseCards("Ah2h3h4h6h");
    assert((815 == eval.EvaluateHand(cards)) && "Utils::WA on Ah2h3h4h6h");

    // this is a straight flush
    cards = Utils::ParseCards("Ah2h3h4h5h");
    assert((815 != eval.EvaluateHand(cards)) && "Utils::WA on Ah2h3h4h5h");
}

// Test that straigths work.
void test_straights() {
    std::vector<u32> cards = Utils::ParseCards("JcTc9c8c7h");
    assert((1603 == eval.EvaluateHand(cards)) && "Utils::WA on JTc9c8c7h");

    cards = Utils::ParseCards("AdKdQdJcTs");
    assert((1600 == eval.EvaluateHand(cards)) && "Utils::WA on AdKdQdJcTs");

    cards = Utils::ParseCards("TsQdAdKdJc");
    assert((1600 == eval.EvaluateHand(cards)) && "Utils::WA on TsQdAdKdJc");

    cards = Utils::ParseCards("Ad2h3h4h5c");
    assert((1609 == eval.EvaluateHand(cards)) && "Utils::WA on Ad2h3h4h5c");

    // this is a straight flush
    cards = Utils::ParseCards("Ah2h3h4h5h");
    assert((1609 != eval.EvaluateHand(cards)) && "Utils::WA on Ah2h3h4h5h");
}

// Test that trips work.
void test_trips() {
    std::vector<u32> cards = Utils::ParseCards("JcJdJs8c7h");
    assert((1853 == eval.EvaluateHand(cards)) && "Utils::WA on JcJdJs8c7h");

    cards = Utils::ParseCards("AdAhAcQs2h");
    assert((1630 == eval.EvaluateHand(cards)) && "Utils::WA on AdAhAcQs2h");

    cards = Utils::ParseCards("4sQd4d4c3s");
    assert((2298 == eval.EvaluateHand(cards)) && "Utils::WA on 4sQd4d4c3s");

    cards = Utils::ParseCards("TsTdJdKdTc");
    assert((1886 == eval.EvaluateHand(cards)) && "Utils::WA on TsTdJdKdTc");
}

// Test that two pairs work.
void test_two_pairs() {
    std::vector<u32> cards = Utils::ParseCards("JdJh7s7cAd");
    assert((2864 == eval.EvaluateHand(cards)) && "Utils::WA on JdJh7s7cAd");

    cards = Utils::ParseCards("2d2s4d4s7h");
    assert((3311 == eval.EvaluateHand(cards)) && "Utils::WA on 2d2s4d4s7h");

    cards = Utils::ParseCards("6dKh8cKc6h");
    assert((2671 == eval.EvaluateHand(cards)) && "Utils::WA on 6dKh8cKc6h");
}

// Test that pairs work.
void test_pairs() {
    std::vector<u32> cards = Utils::ParseCards("2d2h5d4c3c");
    assert((6185 == eval.EvaluateHand(cards)) && "Utils::WA on 2d2h5d4c3c");

    cards = Utils::ParseCards("TcAcTh9dKs");
    assert((4208 == eval.EvaluateHand(cards)) && "Utils::WA on TcAcTh9dKs");

    cards = Utils::ParseCards("3dTdJs7s3c");
    assert((5884 == eval.EvaluateHand(cards)) && "Utils::WA on 3dTdJs7s3c");

    cards = Utils::ParseCards("AdAhKsQcJh");
    assert((3326 == eval.EvaluateHand(cards)) && "Utils::WA on AdAhKsQcJh");
}

// Test that high cards work.
void test_high_cards() {
    std::vector<u32> cards = Utils::ParseCards("7d5c4s3h2d");
    assert((7462 == eval.EvaluateHand(cards)) && "Utils::WA on 7d5c4s3h2d");

    cards = Utils::ParseCards("4h5cJh9d7s");
    assert((7291 == eval.EvaluateHand(cards)) && "Utils::WA on 4h5cJh9d7s");

    cards = Utils::ParseCards("AdKhQsJc9h");
    assert((6186 == eval.EvaluateHand(cards)) && "Utils::WA on AdKhQsJc9h");
}

// Test the function GetBestHand.
void test_get_best_hand() {
    // royal flush vs straight flush vs 2 pair
    std::vector<u32> cards = Utils::ParseCards("AcKcQcJcTcAhTd");
    int expected = eval.EvaluateHand(Utils::ParseCards("AcKcQcJcTc"));
    assert(expected == eval.GetBestHand(cards) && "WA on GetBestHand royal flush");

    // straight vs flush
    cards = Utils::ParseCards("AdKdQdJsTd2dQh");
    expected = eval.EvaluateHand(Utils::ParseCards("AdKdQdTd2d"));
    assert(expected == eval.GetBestHand(cards) && "WA on GetBestHand flush");

    // quad vs boat
    cards = Utils::ParseCards("4d4c4h4s3c3h3s");
    expected = eval.EvaluateHand(Utils::ParseCards("4d4c4h4s3h"));
    assert(expected == eval.GetBestHand(cards) && "WA on GetBestHand quads");

    // trips
    cards = Utils::ParseCards("3c3s3dAdKdQdTs");
    expected = eval.EvaluateHand(Utils::ParseCards("3c3s3dAdKd"));
    assert(expected == eval.GetBestHand(cards) && "WA on GetBestHand trips");
}

int main() {
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
    test_get_best_hand();
}
