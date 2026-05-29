#pragma once
#include <iostream>
#include "Map.h"
#include "GraphTools.h"
#include "Validation.h"
using namespace std;
class GraphManager
{
private:
	Map map;
	string error;
	GraphList* graphPtr;
public:
	GraphManager();
	~GraphManager();

	void LoadMap();
	void DisplayMap();
	void LoadGraph();
	void DisplayGraph();
	void DFS();
	void BFS();

	// Menu part
	void FileMenu();
	void MainMenu();
	void MDSHeader();
	void Run();
};

