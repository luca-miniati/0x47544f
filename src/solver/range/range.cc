//
// Created by luca miniati on 12/24/24.
//

#include "range.h"

Range::Range(std::unique_ptr<std::unordered_map<std::string,
	std::unordered_map<std::shared_ptr<PreflopAction>, double>>> frequencies)
: frequencies(std::move(frequencies)) {}

double Range::Get(const std::shared_ptr<PreflopAction> &action, const std::string &hand) const {
	if (!frequencies->contains(hand))
		throw std::invalid_argument("Hand not recognized: " + hand);
	if (!frequencies->at(hand).contains(action))
		return -1.0;
	return frequencies->at(hand)[action];
}
