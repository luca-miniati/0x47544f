//
// Created by luca miniati on 12/24/24.
//

#include "range.h"
#include <string>

Range::Range(std::unique_ptr<std::unordered_map<std::string,
	std::unordered_map<std::shared_ptr<PreflopAction>, double>>> frequencies)
: frequencies(std::move(frequencies)) {}

double Range::Get(const std::shared_ptr<PreflopAction> &action, const std::string &hand) const {
	if (!frequencies->contains(hand))
	// error was on this line so I changed it for now
		throw std::invalid_argument(std::string("Hand not recognized: ").append(hand));
	if (!frequencies->at(hand).contains(action))
		return -1.0;
	return frequencies->at(hand)[action];
}
