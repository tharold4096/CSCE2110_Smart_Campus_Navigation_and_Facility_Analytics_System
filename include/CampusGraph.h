#ifndef CAMPUSGRAPH_H
#define CAMPUSGRAPH_H
#include <string>
#include <vector>

class CampusGraph {
private:
	//this is one campus building
	struct Building {
		std::string name;
		std::vector<int> neighbors;
	};
	//stores accepted building
	std::vector<Building> buildings;

	//# of undirected connections
	int connectionCount = 0;

	//finds index of building name 
	int findBuilding(const std::string& name) const;

public:
	// adds building if it doesnt exists 
	bool addBuilding(const std::string& name);


	// add undirected connection 
	bool addConnection(const std::string& first, const std::string& second);

	//checks if building exists
	bool hasBuilding(const std::string& name) const;

	//returns the accepted spelling of a building name.
	std::string getbuildingName(const std::string& name) const;

	//show all buildings and neighbors
	void displayGraph() const;

	//displays building counts, connections, and degrees
	void displayStatistics() const;

	//finds reachable buildings using BFS
	void bfsReachable(const std::string& start) const;

};


#endif
