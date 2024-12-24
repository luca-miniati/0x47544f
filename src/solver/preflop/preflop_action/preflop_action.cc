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
	// folding is legal only if there's an outstanding bet to respond to
	auto [p1_bet, p2_bet] = Utils::ComputeOutstandingBets(p1_stack_depth, p2_stack_depth, history);
	
	if (GetPlayer() == 1) {
		// p1 can fold only if p2 has made a higher bet
		return p2_bet > p1_bet;
	} else {
		// p2 can fold only if p1 has made a higher bet
		return p1_bet > p2_bet;
	}
}

double Fold::GetBetAmount(int p1_stack_depth, int p2_stack_depth,
	const std::vector<std::shared_ptr<PreflopAction>>& history) const {
	// folding does not require any bet
	return 0.0;
}

std::size_t Fold::Hash() const {
	return std::hash<int>{}(GetPlayer());
}

bool Fold::isTerminal(const std::vector<std::shared_ptr<PreflopAction>>& history) const {
	// folding is always terminal
	return true;
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

bool Check::isTerminal(const std::vector<std::shared_ptr<PreflopAction>>& history) const {
	// in preflop, heads-up, checking is terminal
	return true;
}

// BetProportionPot

bool BetProportionPot::IsLegal(int p1_stack_depth, int p2_stack_depth,
	const std::vector<std::shared_ptr<PreflopAction>>& history) const {
	auto [p1_bet, p2_bet] = Utils::ComputeOutstandingBets(p1_stack_depth, p2_stack_depth, history);
	int curr_player_stack = (GetPlayer() == 1) ? p1_stack_depth : p2_stack_depth;
	double req_amount = GetBetAmount(p1_stack_depth, p2_stack_depth, history);
	double min_raise = Utils::ComputeMinimumRaise(p1_bet, p2_bet, history);
	
	// a valid bet must be at least the minimum raise and within the player's stack
	return (req_amount >= min_raise) && (req_amount <= curr_player_stack);
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

bool BetProportionPot::isTerminal(const std::vector<std::shared_ptr<PreflopAction>>& history) const {
	// in preflop, heads-up, betting is not terminal
	return false;
}

// BetMultiple

bool BetMultiple::IsLegal(int p1_stack_depth, int p2_stack_depth,
	const std::vector<std::shared_ptr<PreflopAction>>& history) const {
	// betting a multiple of the current bet is legal if the player has enough chips
	auto [p1_bet, p2_bet] = Utils::ComputeOutstandingBets(p1_stack_depth, p2_stack_depth, history);

	if (p1_bet == p2_bet && (bet_multiplier > 1 && bet_multiplier < 2) && bet_multiplier < 1) { 
		return false;
	}

	double req_amount = GetBetAmount(p1_stack_depth, p2_stack_depth, history);
	int curr_player_stack = (GetPlayer() == 1) ? p1_stack_depth : p2_stack_depth;
	return req_amount <= curr_player_stack;
}

double BetMultiple::GetBetAmount(int p1_stack_depth, int p2_stack_depth,
	const std::vector<std::shared_ptr<PreflopAction>>& history) const {
	// Get current outstanding bets
	auto [p1_bet, p2_bet] = Utils::ComputeOutstandingBets(p1_stack_depth, p2_stack_depth, history);
	
	// find the last raise amount
	double curr_bet = std::max(p1_bet, p2_bet);
	double prev_bet = std::min(p1_bet, p2_bet);
	double last_raise = curr_bet - prev_bet;
	
	// bet is a multiple of the last raise amount
	return last_raise * bet_multiplier;
}

std::size_t BetMultiple::Hash() const {
	std::size_t seed = std::hash<int>{}(GetPlayer());
	Utils::HashCombine(seed, std::hash<double>{}(bet_multiplier));
	return seed;
}

bool BetMultiple::isTerminal(const std::vector<std::shared_ptr<PreflopAction>>& history) const {
	if (bet_multiplier == 1) {
		// if the bet multiplier is 1, then the bet is terminal
		return true;
	} else {
		// if the bet multiplier is not 1, then the bet is not terminal
		return false;
	}
}

// BetAllIn

bool BetAllIn::IsLegal(int p1_stack_depth, int p2_stack_depth,
	const std::vector<std::shared_ptr<PreflopAction>>& history) const {
	auto [p1_bet, p2_bet] = Utils::ComputeOutstandingBets(p1_stack_depth, p2_stack_depth, history);

	int curr_player_stack = (GetPlayer() == 1) 
		? p1_stack_depth - p1_bet 
		: p2_stack_depth - p2_bet;
		
	return curr_player_stack > 0;
}

double BetAllIn::GetBetAmount(int p1_stack_depth, int p2_stack_depth,
	const std::vector<std::shared_ptr<PreflopAction>>& history) const {
	auto [p1_bet, p2_bet] = Utils::ComputeOutstandingBets(p1_stack_depth, p2_stack_depth, history);
	
	double remaining_stack = (GetPlayer() == 1) 
		? p1_stack_depth - p1_bet 
		: p2_stack_depth - p2_bet;
		
	return remaining_stack;
}

std::size_t BetAllIn::Hash() const {
	return std::hash<int>{}(GetPlayer());
}

bool BetAllIn::isTerminal(const std::vector<std::shared_ptr<PreflopAction>>& history) const {
	// all-in bet is not terminal
	return false;
}
