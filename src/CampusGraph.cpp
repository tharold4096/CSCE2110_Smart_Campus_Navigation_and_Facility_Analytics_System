#include "CampusGraph.h"
#include <cctype>

namespace {

	//removes whitespace 
	std::string trimName(const std::string& text) {
		const std::string whitespace = " \t\r\n";

		size_t first = text.find_first_not_of(whitespace);

		if (first == std::string::npos) {
			return "";
		}
		size_t last = text.find_last_not_of(whitespace);

		return text.substr(first, last - first + 1);
	}
	// makes names comparable without case sensitive
	std::string normalizeName(const std::string& name) {
		std::string result = trimName(name);

		for (char& c : result) {
			c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
		}

		return result;
	}
}

// finds buildings index 
int CampusGraph::findBuilding(const std::string& name) const {
	std::string target = normalizeName(name);

	for (size_t i = 0; i < buildings.size(); i++) {
		if (normalizeName(buildings[i].name) == target) {
			return static_cast<int>(i);
		}
	}

	return -1;
}

// adds building unless name is empty or dup
bool CampusGraph::addBuilding(const std::string& name) {
	std::string cleanName = trimName(name);
	
	if (cleanName.empty() || findBuilding(cleanName) != -1) {
		return false;
	}

	buildings.push_back({ cleanName, {} });
	return true;
}
// checks if building already exists
bool CampusGraph::hasBuilding(const std::string& name) const {
	return findBuilding(name) != -1;
}
// returns original spelling of building
std::string CampusGraph::getBuildingName(
	const std::string& name) const {
	int index = findBuilding(name);

	if (index == -1) {
		return "";
	}

	return buildings[index].name;
}