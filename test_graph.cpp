#include "CampusGraph.h"
#include <iostream>

int main() {
	CampusGraph graph;


	graph.addBuilding("Library");
	graph.addBuilding("Union");
	graph.addBuilding("Gym");
	graph.addBuilding("Discovery");

	//test for dup rejection
	std::cout << "Duplicate building accepted? " << graph.addBuilding("library") << "\n";

	// connecting 3 buildings
	graph.addConnection("Library", "Union");
	graph.addConnection("Union", "Gym");

	//test invalid connection
	std::cout << "Duplicate connection accepted? " << graph.addConnection("Union", "Library") << "\n";
	std::cout << "Self connection accepted? " << graph.addConnection("Gym", "Gym") << "\n";

	//display the graph
	std::cout << "\n---- Campus Graph ----\n";
	graph.displayGraph();

	// display stats
	std::cout << "\n---- Statistics ----\n";
	graph.displayStatistics();

	//test BFS
	std::cout << "\n---- BFS from library ----\n";
	graph.bfsReachable("library");

	//test an isolated building
	std::cout << "\n---- BFS from Discovery ----\n";
	graph.bfsReachable("Discovery");

	return 0;
}