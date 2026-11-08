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

	// test for loading buildings from a file
	std::cout << "\n--- Testing File Loading ---\n";

	CampusGraph fileGraph;

	fileGraph.loadBuildings("data/buildings.txt");
	fileGraph.loadConnections("data/connections.txt");

	fileGraph.displayGraph();
	fileGraph.displayStatistics();

	std::cout << "\n--- BFS from Library ---\n";
	fileGraph.bfsReachable("Library");

	//testing for BFS from an isolated buildin
	std::cout << "\n--- BFS from Observatory ---\n";
	fileGraph.bfsReachable("Observatory");

	// testing for BFS from a building that doesnt exist
	std::cout << "\n---- BFS from Unknown Building ----\n";
	fileGraph.bfsReachable("Fake Building");

	// testing for BFS with lowercase input
	std::cout << "\n---- BFS with Lowercase Name ----\n";
	fileGraph.bfsReachable("library");


	// test invalid campus data.
	std::cout << "\n---- Invalid Data Tests ----\n";
	CampusGraph invalidGraph;
	invalidGraph.loadBuildings("testdata/buildings.txt");
	invalidGraph.loadConnections("testdata/connections.txt");
	invalidGraph.displayGraph();
	invalidGraph.displayStatistics();


	// test missing files.
	std::cout << "\n--- Missing File Tests ---\n";
	CampusGraph missingGraph;
	missingGraph.loadBuildings("testdata/missing.txt");
	missingGraph.loadConnections("testdata/missing2.txt");
	missingGraph.displayStatistics();


	return 0;
}