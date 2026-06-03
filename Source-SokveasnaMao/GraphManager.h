#pragma once
#include <iostream>
#include "Map.h"
#include "GraphTools.h"
#include "Validation.h"
#include "PathFinder.h"
using namespace std;

class GraphManager
{
private:
	Map map; // store the map loaded from file, used for graph construction and A* path finding
	string error; // store error message from map loading and validation to display in Manager
	GraphList* graphPtr; // store the graph constructed from map, used for DFS and BFS
	PathFinder pathFinder; // store the path finder for A* algorithm, used for A* path finding and saving path to file
public:
	GraphManager();
	~GraphManager();

	// helper function
	bool GraphReady() const; // return TRUE if graph and map is loaded successfully
	void ClearScreen();

	// core functions
	void LoadMapFromFile();
	void DisplayMap();
	void LoadGraphFromMap();
	void DisplayGraph();
	void RunDFS();
	void RunBFS();
	void RunAStar();
	void SaveAStarPath();

	// menu part
	void FileMenu();
	void MainMenu();
	void MDSHeader();

	// application
	void Run();
};

