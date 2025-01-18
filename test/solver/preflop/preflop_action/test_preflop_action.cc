#include <gtest/gtest.h>
#include "solver/preflop/preflop_action/preflop_action.h"
#include <memory>
#include <vector>

class TestPreflopAction : public testing::Test {
protected:
    void SetUp() override {
        // Setup common actions used across tests
        fold = PreflopAction::Fold();
        check = PreflopAction::Check();
        call = PreflopAction::Call();
        min_raise = PreflopAction::Raise(2);
        x5_raise = PreflopAction::Raise(5);
        all_in = PreflopAction::AllIn();

        // Empty history for tests
        mt_history = {};
    }

    // Define actions
    std::shared_ptr<PreflopAction> fold;
    std::shared_ptr<PreflopAction> check;
    std::shared_ptr<PreflopAction> call;
    std::shared_ptr<PreflopAction> min_raise;
    std::shared_ptr<PreflopAction> x5_raise;
    std::shared_ptr<PreflopAction> all_in;

    // Empty history
    std::vector<std::shared_ptr<PreflopAction> > mt_history;

    // Common stack size for tests
    static constexpr int BB_100 = 100;
};

TEST_F(TestPreflopAction, IsLegalFold) {
    EXPECT_TRUE(fold->IsLegal({2, 0, 1, BB_100, BB_100, {x5_raise}, 4}))
        << "Should be able to fold with outstanding bet";

    // EXPECT_TRUE(fold->IsLegal({1, 0, 1, BB_100,
    //     BB_100, {x5_raise, x5_raise}, 4}))
    //     << "Should be able to fold with outstanding bet";
    //
    // EXPECT_TRUE(fold->IsLegal({1, 0, 1, BB_100,
    //     BB_100, mt_history, 4}))
    //     << "Should be able to fold at the start";
    //
    // EXPECT_FALSE(fold->IsLegal({2, 0, 1, BB_100,
    //     BB_100, mt_history, 4}))
    //     << "Should not be able to fold out of turn";
    //
    // EXPECT_FALSE(fold->IsLegal({2, 0, 1, BB_100,
    //     BB_100, {call}, 4}))
    //     << "Should not be able to fold with no outstanding bet";
}

TEST_F(TestPreflopAction, IsLegalCheck) {
    // EXPECT_TRUE(check->IsLegal({2, 0, 1, BB_100,
    //     BB_100, {call}, 4}))
    //     << "Should be able to check with no outstanding bet";
    //
    // EXPECT_FALSE(check->IsLegal({2, 0, 1, BB_100,
    //     BB_100, mt_history, 4}))
    //     << "Should not be able to check out of turn";
    //
    // EXPECT_FALSE(check->IsLegal({2, 0, 1, BB_100,
    //     BB_100, {min_raise, min_raise}, 4}))
    //     << "Should not be able to check out of turn";
    //
    // EXPECT_FALSE(check->IsLegal({1, 0, 1, BB_100,
    //     BB_100, mt_history, 4}))
    //     << "Should not be able to check with outstanding bet";
    //
    // EXPECT_FALSE(check->IsLegal({2, 0, 1, BB_100,
    //     BB_100, {min_raise}, 4}))
    //     << "Should not be able to check with outstanding bet";
    //
    // EXPECT_FALSE(check->IsLegal({2, 0, 1, BB_100,
    //     BB_100, {all_in}, 4}))
    //     << "Should not be able to check with outstanding bet";
    //
    // EXPECT_FALSE(check->IsLegal({1, 0, 1, BB_100,
    //     BB_100, {min_raise, call}, 4}))
    //     << "Should not be able to check after action is over";
}

TEST_F(TestPreflopAction, IsLegalCall) {
    // EXPECT_TRUE(call->IsLegal(BB_100, BB_100, mt_history, 4))
    //     << "Should be able to call big blind";
    //
    // EXPECT_TRUE(call->IsLegal(BB_100, BB_100, {min_raise}, 4))
    //     << "Should be able to call raise";
    //
    // EXPECT_TRUE(call->IsLegal(BB_100, BB_100, {x5_raise}, 4))
    //     << "Should be able to call raise";
    //
    // EXPECT_TRUE(call->IsLegal(BB_100, BB_100, {x5_raise, x5_raise}, 4))
    //     << "Should be able to call raise";
    //
    // EXPECT_TRUE(call->IsLegal(BB_100, BB_100, {all_in}, 4))
    //     << "Should be able to call all-in";
    //
    // EXPECT_TRUE(call->IsLegal(BB_100, 5, {all_in}, 4))
    //     << "Should be able to call all-in when opponent covers";
    //
    // EXPECT_FALSE(call->IsLegal(BB_100, BB_100, {call}, 4))
    //     << "Should not be able to call without outstanding bet";
    //
    // EXPECT_FALSE(call->IsLegal(BB_100, BB_100, mt_history, 4))
    //     << "Should not be able to call out of turn";
    //
    // EXPECT_FALSE(call->IsLegal(BB_100, BB_100, {call, check}, 4))
    //     << "Should not be able to call after action has finished";
}

TEST_F(TestPreflopAction, IsLegalRaise) {
    // EXPECT_TRUE(min_raise->IsLegal(BB_100, BB_100, mt_history, 4))
    //     << "Should be able to min-raise";
    //
    // EXPECT_TRUE(min_raise->IsLegal(BB_100, BB_100, {min_raise}, 4))
    //     << "Should be able to min-raise after min-raise";
    //
    // EXPECT_TRUE(min_raise->IsLegal(BB_100, BB_100, {call}, 4))
    //     << "Should be able to min-raise after call";
    //
    // EXPECT_TRUE(x5_raise->IsLegal(BB_100, BB_100, {min_raise}, 4))
    //     << "Should be able to 3-bet after min-raise";
    //
    // EXPECT_TRUE(x5_raise->IsLegal(BB_100, BB_100, {min_raise, x5_raise}, 4))
    //     << "Should be able to 4-bet after 3-bet";
    //
    // EXPECT_FALSE(x5_raise->IsLegal(BB_100, 4, {min_raise, min_raise, x5_raise}, 4))
    //     << "Should not be able to 5-bet";
    //
    // EXPECT_FALSE(min_raise->IsLegal(BB_100, BB_100, {min_raise}, 4))
    //     << "Should not be able to raise out of turn";
    //
    // EXPECT_FALSE(min_raise->IsLegal(BB_100, 3, {min_raise}, 4))
    //     << "Should not be able to raise all-in";
    //
    // EXPECT_FALSE(x5_raise->IsLegal(BB_100, 4, {min_raise, min_raise}, 4))
    //     << "Should not be able to raise opponent all-in";
}

TEST_F(TestPreflopAction, IsLegalAllIn) {
    // EXPECT_TRUE(all_in->IsLegal(BB_100, BB_100, mt_history, 4))
    //     << "Should be able to open jam";
    //
    // EXPECT_TRUE(all_in->IsLegal(BB_100, BB_100, {min_raise}, 4))
    //     << "Should be able to 3-bet jam";
    //
    // EXPECT_TRUE(all_in->IsLegal(BB_100, BB_100, {min_raise, min_raise}, 4))
    //     << "Should be able to 4-bet jam";
    //
    // EXPECT_FALSE(
    //     all_in->IsLegal(BB_100, BB_100, {min_raise, min_raise, min_raise, min_raise},
    //         4))
    //     << "Should not be able to 5-bet jam";
    //
    // EXPECT_FALSE(all_in->IsLegal(BB_100, BB_100, {min_raise}, 4))
    //     << "Should not be able to jam out of turn";
}

TEST_F(TestPreflopAction, GetBetAmountFold) {
    // ASSERT_EQ(0, fold->GetBetAmount(BB_100, BB_100, mt_history));
    //
    // ASSERT_EQ(0, fold->GetBetAmount(BB_100, BB_100, {min_raise}));
}

TEST_F(TestPreflopAction, GetBetAmountCheck) {
    // ASSERT_EQ(0, check->GetBetAmount(BB_100, BB_100, {call}));
}

TEST_F(TestPreflopAction, GetBetAmountCall) {
    // ASSERT_EQ(0.5, call->GetBetAmount(BB_100, BB_100, mt_history));
    //
    // ASSERT_EQ(1, call->GetBetAmount(BB_100, BB_100, {min_raise}));
    //
    // ASSERT_EQ(2.5, call->GetBetAmount(BB_100, BB_100, {x5_raise}));
    //
    // ASSERT_EQ(99, call->GetBetAmount(BB_100, BB_100, {all_in}));
}

TEST_F(TestPreflopAction, GetBetAmountRaise) {
}

TEST_F(TestPreflopAction, GetBetAmountAllIn) {
}

TEST_F(TestPreflopAction, Hash) {
}

// Placeholder for future IsTerminal tests
TEST_F(TestPreflopAction, IsTerminal) {
    // TODO: Implement terminal state tests
}
