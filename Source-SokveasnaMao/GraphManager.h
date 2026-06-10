/***************************************************************************
Bachelor of Software Engineering
Media Design School
Auckland, New Zealand
(c) Year 1 Media Design School

Author                  : Sokveasna Mao
Email                   : maosokveasna48@gmail.com
Component code and name : GD1P02 - Algorithms and Data Structures
Name                    : Assessment 2

File                    : PathFinder.h

Description:
	Defines the PathFinder class that implements the A* pathfinding algorithm
	to find a path from a start cell to an exit cell on a Map.
***************************************************************************/

#pragma once
#include <iostream>
#include "Map.h"
#include "GraphTools.h"
#include "Validation.h"
#include "PathFinder.h"
using namespace std;

/*
============================================================
GraphManager Class
============================================================
Purpose:
	- main controller of the application
	- coordinates map loading, graph traversal, and A* algorithm
	- user interaction through menu

Responsibilities:
	- load and validate map
	- construct graph
	- display map and graph
	- execute DFS, BFS and A*
	- save pathfinding result
============================================================
*/
class GraphManager
{
private:
	Map map; // store the map loaded from file, used for graph construction and A* path finding
	string error; // store error message from map loading and validation to display in Manager
	GraphList* graphPtr; // store the graph constructed from map, used for DFS and BFS
	PathFinder pathFinder; // store the path finder for A* algorithm, used for A* path finding and saving path to file
	bool pathFound; // check if path is found or not
public:
	GraphManager(); // default constructor
	~GraphManager(); // destructor

	bool GraphReady() const; // return TRUE if graph and map is loaded successfully
	bool CleanGraph(); // delete graph pointer
	void ClearScreen(); // clear screen

	void LoadMapFromFile(); // load map from file with 2 path option (specific or default)
	void DisplayMap(); // display map with 20x20 grid
	void LoadGraphFromMap(); // load graph from map
	void DisplayGraph(); // display graph in adjacency list
	void RunDFS(); // run DFS
	void RunBFS(); // run BFS
	void RunAStar(); // run AStar
	void DisplayAStarPath(); // display A* path
	void SaveAStarPath(); // save AStar found map to file

	void FileMenu(); // display file menu
	void MainMenu(); // display main menu
	void MDSHeader(); // display MDS header

	void Run(); // run the application
};

