//
// Created by luca miniati on 12/24/24.
//

#include "preflop_action.h"

// Constructors
PreflopAction::PreflopAction(const int player) : player(player) {}
Fold::Fold(const int player) : PreflopAction(player) {}
Check::Check(const int player) : PreflopAction(player) {}
Call::Call(const int player) : PreflopAction(player) {}
BetFixed::BetFixed(const int player, const int bet_amount) : PreflopAction(player),
bet_amount(bet_amount) {}
BetMultiple::BetMultiple(const int player, const int bet_multiplier) : PreflopAction(player),
bet_multiplier(bet_multiplier) {}
BetAllIn::BetAllIn(const int player) : PreflopAction(player) {}

// Static Factory methods
std::shared_ptr<PreflopAction> PreflopAction::Fold(int player) {
	return std::make_shared<::Fold>(player);
}
std::shared_ptr<PreflopAction> PreflopAction::Check(int player) {
	return std::make_shared<::Check>(player);
}
std::shared_ptr<PreflopAction> PreflopAction::BetFixed(int player, double bet_amount) {
	return std::make_shared<::BetFixed>(player, bet_amount);
}
std::shared_ptr<PreflopAction> PreflopAction::BetMultiple(int player, double bet_multiplier) {
	return std::make_shared<::BetMultiple>(player, bet_multiplier);
}
std::shared_ptr<PreflopAction> PreflopAction::BetAllIn(int player) {
	return std::make_shared<::BetAllIn>(player);
}

int PreflopAction::GetPlayer() const {
	return player;
}

// Implementation
bool Fold::IsLegal(int p1_stack_depth, int p2_stack_depth,
	const std::vector<std::shared_ptr<PreflopAction>>& history) const {
	return true;
}

