
#include "CampusGraph.h"
#include <cctype>
#include <iostream>
#include <queue>

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
std::string CampusGraph::getBuildingName(const std::string& name) const {
	int index = findBuilding(name);

	if (index == -1) {
		return "";
	}

	return buildings[index].name;
}

// adding undirected connections between two buildings and rejecting unknowns, self connects and dups

bool CampusGraph::addConnection(
	const std::string& first,
	const std::string& second) {


	//find both buildings 
	int indexA = findBuilding(first);
	int indexB = findBuilding(second);

	//reject unknowns
	if (indexA == -1 || indexB == -1) {
		return false;
	}


	// building cannot connect to itsself
	if (indexA == indexB) {
		return false;
	}

	//checks for connection
	for (int neighbor : buildings[indexA].neighbors) {
		if (neighbor == indexB) {
			return false;
		}
	}

	// add connections in both directions
	buildings[indexA].neighbors.push_back(indexB);
	buildings[indexB].neighbors.push_back(indexA);

	connectionCount++;

	return true;
}


//displays all building and its connections 
void CampusGraph::displayGraph() const {
	if (buildings.empty()) {
		std::cout << "No buildings available. \n";
		return;

	}

	for (const Building& building : buildings) {
		std::cout << building.name << ": ";
		if (building.neighbors.empty()) {
			std::cout << "(no connections)";
		}
		else {
			for (int index : building.neighbors) {
				std::cout << buildings[index].name << " ";
			}
		}
		std::cout << "\n";

	}
}

// display the graph counts and degrees

void CampusGraph::displayStatistics() const {
	std::cout << "Total buildings: " << buildings.size() << "\n";
	std::cout << "Total connections: " << connectionCount << "\n";

	if (buildings.empty()) {
		std::cout << "No buildings available \n";
		return;
	}

	for (const Building& building : buildings) {
		std::cout << building.name << ": degree " << building.neighbors.size() << "\n";
	}
}

//finding all buildings that are reachable from a starting building using bfs

void CampusGraph::bfsReachable(const std::string& start) const {
	int startIndex = findBuilding(start);
	if (startIndex == -1) {
		std::cout << "Unknown building: " << start << "\n";
		return;
	}

	// setting up the queue, visited list and the distances
	std::queue<int> q;
	std::vector<bool> visited(buildings.size(), false);
	std::vector<int> distance(buildings.size(), 0);

	//start of 
	q.push(startIndex);
	visited[startIndex] = true;
	int reachableCount = 0;
	while (!q.empty()) {
		int current = q.front();
		q.pop();
		std::cout << buildings[current].name << " (distance " << distance[current] << ") \n";
		reachableCount++;

		//check neighboring buildings
		for (int neighbor : buildings[current].neighbors) {
			if (!visited[neighbor]) {
				visited[neighbor] = true;
				distance[neighbor] = distance[current] + 1;
				q.push(neighbor);
			}
		}
	}
	std::cout << "Reachable: " << reachableCount << " of " << buildings.size() << " buildings\n";
}