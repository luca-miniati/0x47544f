//
// Created by luca miniati on 12/24/24.
//

#include "preflop_action.h"
#include "../../utils/utils.h"
#include <memory>

// Constructors
PreflopAction::PreflopAction(const int player) : player(player) {}
Fold::Fold(const int player) : PreflopAction(player) {}
Check::Check(const int player) : PreflopAction(player) {}
BetProportionPot::BetProportionPot(const int player, const double bet_multiplier) : PreflopAction(player),
bet_multiplier(bet_multiplier) {}
BetMultiple::BetMultiple(const int player, const double bet_multiplier) : PreflopAction(player),
bet_multiplier(bet_multiplier) {}
BetAllIn::BetAllIn(const int player) : PreflopAction(player) {}

// Static Factory methods
std::shared_ptr<PreflopAction> PreflopAction::Fold(int player) {
	return std::make_shared<::Fold>(player);
}
std::shared_ptr<PreflopAction> PreflopAction::Check(int player) {
	return std::make_shared<::Check>(player);
}
std::shared_ptr<PreflopAction> PreflopAction::BetProportionPot(int player, double bet_multiplier) {
	return std::make_shared<::BetProportionPot>(player, bet_multiplier);
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

// Fold

bool Fold::IsLegal(int p1_stack_depth, int p2_stack_depth,
	const std::vector<std::shared_ptr<PreflopAction>>& history) const {
	// folding is always legal
	return true;
}

double Fold::GetBetAmount(int p1_stack_depth, int p2_stack_depth,
	const std::vector<std::shared_ptr<PreflopAction>>& history) const {
	// folding does not require any bet
	return 0.0;
}

std::size_t Fold::Hash() const {
	return std::hash<int>{}(GetPlayer());
}

// Check

bool Check::IsLegal(int p1_stack_depth, int p2_stack_depth,
	const std::vector<std::shared_ptr<PreflopAction>>& history) const {
	// checking is legal only if there is no outstanding bet to call
	auto [p1_bet, p2_bet] = Utils::ComputeOutstandingBets(p1_stack_depth, p2_stack_depth, history);
	return p1_bet == p2_bet;
}

double Check::GetBetAmount(int p1_stack_depth, int p2_stack_depth,
	const std::vector<std::shared_ptr<PreflopAction>>& history) const {
	// checking does not involve any bet
	return 0.0;
}	

std::size_t Check::Hash() const {
	return std::hash<int>{}(GetPlayer());
}

// BetProportionPot

bool BetProportionPot::IsLegal(int p1_stack_depth, int p2_stack_depth,
	const std::vector<std::shared_ptr<PreflopAction>>& history) const {
	// betting a proportion of the pot is always legal as long as the player has enough chips
	auto [p1_bet, p2_bet] = Utils::ComputeOutstandingBets(p1_stack_depth, p2_stack_depth, history);
	double req_amount = GetBetAmount(p1_stack_depth, p2_stack_depth, history);
	int curr_player_stack = (GetPlayer() == 1) ? p1_stack_depth : p2_stack_depth;
	return req_amount <= curr_player_stack;
}

double BetProportionPot::GetBetAmount(int p1_stack_depth, int p2_stack_depth,
	const std::vector<std::shared_ptr<PreflopAction>>& history) const {
	// calculate the current pot
	auto [p1_bet, p2_bet] = Utils::ComputeOutstandingBets(p1_stack_depth, p2_stack_depth, history);
	double pot = p1_bet + p2_bet;
	// bet is a proportion of the pot
	return pot * bet_multiplier;
}

std::size_t BetProportionPot::Hash() const {
	std::size_t seed = std::hash<int>{}(GetPlayer());
	Utils::HashCombine(seed, std::hash<double>{}(bet_multiplier));
	return seed;
}

// BetMultiple

bool BetMultiple::IsLegal(int p1_stack_depth, int p2_stack_depth,
	const std::vector<std::shared_ptr<PreflopAction>>& history) const {
	// betting a multiple of the current bet is legal if the player has enough chips
	auto [p1_bet, p2_bet] = Utils::ComputeOutstandingBets(p1_stack_depth, p2_stack_depth, history);
	double current_bet = std::max(p1_bet, p2_bet);
	double req_amount = GetBetAmount(p1_stack_depth, p2_stack_depth, history);
	int curr_player_stack = (GetPlayer() == 1) ? p1_stack_depth : p2_stack_depth;
	return req_amount <= curr_player_stack;
}

double BetMultiple::GetBetAmount(int p1_stack_depth, int p2_stack_depth,
	const std::vector<std::shared_ptr<PreflopAction>>& history) const {
	// calculate the current bet to multiply
	auto [p1_bet, p2_bet] = Utils::ComputeOutstandingBets(p1_stack_depth, p2_stack_depth, history);
	double curr_bet = std::max(p1_bet, p2_bet);
	// bet is a multiple of the current bet
	return curr_bet * bet_multiplier;
}

std::size_t BetMultiple::Hash() const {
	std::size_t seed = std::hash<int>{}(GetPlayer());
	Utils::HashCombine(seed, std::hash<double>{}(bet_multiplier));
	return seed;
}

// BetAllIn

bool BetAllIn::IsLegal(int p1_stack_depth, int p2_stack_depth,
	const std::vector<std::shared_ptr<PreflopAction>>& history) const {
	// all-in is always legal unless the player is already all-in
	int curr_player_stack = (GetPlayer() == 1) ? p1_stack_depth : p2_stack_depth;
	return curr_player_stack > 0;
}

double BetAllIn::GetBetAmount(int p1_stack_depth, int p2_stack_depth,
	const std::vector<std::shared_ptr<PreflopAction>>& history) const {
	// all-in bet is the player's remaining stack
	return (GetPlayer() == 1) ? p1_stack_depth : p2_stack_depth;
}

std::size_t BetAllIn::Hash() const {
	return std::hash<int>{}(GetPlayer());
}