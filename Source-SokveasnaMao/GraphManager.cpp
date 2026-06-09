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

#include "GraphManager.h"

/*==================Graph Manager constructor========================*/
GraphManager::GraphManager()
{
	graphPtr = nullptr;
}

/*==================Graph Manager destructor========================*/
GraphManager::~GraphManager()
{
	if (graphPtr != nullptr) {
		delete graphPtr;
		graphPtr = nullptr;
	}
}

/*==================Load Map From File========================*/
void GraphManager::LoadMapFromFile()
{
	try {
		FileMenu();
		int pathOption = Validation::ValidateIntInput("Enter option: ", 0, 2);
		if (pathOption == 0) return;

		string filePath;

		// input for specific path
		if (pathOption == 1) {
			cout << "Enter file path to load inventory: ";
			getline(cin, filePath);
		}
		// input for default
		else if (pathOption == 2) {
			filePath = "C:\\School\\Year 1 term 2\\Algorithm & Data Structure\\Assignment 2\\ExampleMaps\\ExampleMaps\\ValidMap2.txt";
		}

		// validate filepath
		if (!Validation::ValidateFilePath(filePath)) {
			cout << "LoadMap: fail to load map from " << filePath << endl;
			return;
		}

		// load map from file
		if (!map.LoadFromFile(filePath, error)) {
			cout << "LoadMap error: " << error << endl;
			return;
		}
		cout << "Load map successfully from " << filePath << endl;
	}
	catch (exception& e) {
		cout << "LoadMap error: " << e.what() << endl;
		return;
	}
}

/*==================Display Map========================*/
void GraphManager::DisplayMap()
{
	try {
		if(!map.IsMapLoaded()) {
			cout << "DisplayMap: no map loaded" << endl;
			return;
		}
		map.DisplayMap();
	}
	catch (exception& e) {
		cout << "DisplayMap error: " << e.what() << endl;
		return;
	}
}

/*==================Load Grpah From Map========================*/
void GraphManager::LoadGraphFromMap()
{
	try {
		if(!map.IsMapLoaded()) {
			cout << "LoadGraphFromMap: no map loaded" << endl;
			return;
		}
		// remove existing graph
		CleanGraph();

		graphPtr = GraphTools::GetGraphFromMap(&map);
		cout << "Graph loaded successfully from map" << endl;
	}
	catch (exception& e) {
		cout << "LoadGraphFromMap error: " << e.what() << endl;
		return;
	}
}

/*==================Display Graph========================*/
void GraphManager::DisplayGraph() {
	try {
		if (!GraphReady()) {
			cout << "DisplayGraph: graph is not ready to display" << endl;
			return;
		}
		GraphTools::DisplayGraphList(graphPtr);
		// check node distance 
		// cause the distance is different from the example shown in assignment
		// GraphTools::PrintAllNodeDistances(&map);
	}
	catch (exception& e) {
		cout << "DisplayGraph error: " << e.what() << endl;
		return;
	}
}

/*==================Run DFS========================*/
void GraphManager::RunDFS()
{
	try {
		if (!GraphReady()) {
			cout << "RunDFS: graph is not ready to run DFS" << endl;
			return;
		}
		GraphTools::DFS(graphPtr, 's'); // assuming 's' exists
		cout << "Run DFS successfully" << endl;
	}
	catch (exception& e) {
		cout << "RunDFS error: " << e.what() << endl;
		return;
	}
}

/*==================Run BFS========================*/
void GraphManager::RunBFS()
{
	try {
		if (!GraphReady()) {
			cout << "RunBFS: graph is not ready to run BFS" << endl;
			return;
		}
		GraphTools::BFS(graphPtr, 's'); // assuming 's' exists
		cout << "Run BFS successfully" << endl;
	}
	catch (exception& e) {
		cout << "RunBFS error: " << e.what() << endl;
		return;
	}
}

/*==================Run A*========================*/
void GraphManager::RunAStar()
{
	try {
		if (!GraphReady()) {
			cout << "RunAStar: graph is not ready to run A* algorithm" << endl;
			return;
		}

		int startR, startC, exitR, exitC;
		map.SetStartPosition(startR, startC);
		map.SetExitPosition(exitR, exitC);
	
		bool found = pathFinder.FindPath(&map, { startR, startC }, { exitR, exitC });

		if (!found) {
			cout << "RunAStar: no path can be found" << endl;
			return;
		}

		pathFinder.DisplayPath(&map);
		cout << "Run A* successfully" << endl;
	}
	catch (exception& e) {
		cout << "RunAStar error: " << e.what() << endl;
		return;
	}
}

/*==================Save A* path========================*/
void GraphManager::SaveAStarPath()
{
	try {
		if(!pathFinder.PathFound()) {
			cout << "SaveAStarPath: no valid path to save" << endl;
			return;
		}
		cout << "File menu" << endl;
		FileMenu();
		int choice = Validation::ValidateIntInput("Enter choice: ", 0, 2);

		switch (choice) {
		case 1: {
			string filename;
			cout << "Enter filename: " << endl;
			getline(cin, filename);

			if (filename.empty()) {
				cout << "RunAStar: No filename entered. Save cancelled" << endl;
				return;
			}

			if (!Validation::ValidateFilePath(filename)) {
				cout << "RunAStar: invalid filename. must end with .txt." << endl;
				return;
			}
			bool saved = pathFinder.SavePath(&map, filename);
			cout << (saved ? "RunAStar: path saved to " + filename : "RunAStar: fail to save file") << endl;

			break;
		}
		case 2: {
			string defaultFile = "pathOutput.txt";
			bool saved = pathFinder.SavePath(&map, defaultFile);

			cout << (saved ? "RunAStar: path saved to " + defaultFile : "RunAStar: fail to save file") << endl;
			break;
		}
		case 0: return;
		default:
			cout << "Invalid input" << endl;
			break;
		}
	}
	catch (exception& e) {
		cout << "SaveAStarPath error: " << e.what() << endl;
		return;
	}
}

/*==================Graph Ready========================*/
bool GraphManager::GraphReady() const
{
	if (!map.IsMapLoaded()) {
		cout << "No map loaded.\n";
		return false;
	}

	if (graphPtr == nullptr) {
		cout << "No graph loaded.\n";
		return false;
	}

	return true;
}

/*==================Clean Grpah========================*/
bool GraphManager::CleanGraph()
{
	if (graphPtr != nullptr) {
		delete graphPtr;
		graphPtr = nullptr;
		return true;
	}
	return false;
}

/*==================Clear Screen========================*/
void GraphManager::ClearScreen()
{
	system("cls");
}

/*==================File Menu========================*/
void GraphManager::FileMenu()
{
	cout << "1. Specific path" << endl;
	cout << "2. Default" << endl;
	cout << "0. Back" << endl;
}

/*==================MainMenu========================*/
void GraphManager::MainMenu()
{
	cout << "------Main Menu-------" << endl;
	cout << "1. Load Map from file" << endl;
	cout << "2. Display Map" << endl;
	cout << "3. Load Graph from Map" << endl;
	cout << "4. Display Graph" << endl;
	cout << "5. Run DFS" << endl;
	cout << "6. Run BFS" << endl;
	cout << "7. Run AStar" << endl;
	cout << "8. Save AStar Path" << endl;
	cout << "0. Exit" << endl;
}
/*==================MDSHeader========================*/
void GraphManager::MDSHeader() {
	cout << "***********************************************************************\n\n";
	cout << "Bachelor of Software Engineering\n";
	cout << "Media Design School\n";
	cout << "Auckland,    New Zealand\n";
	cout << "(c) Year 1 Media Design School\n\n";
	cout << "Author                  :   Sokveasna Mao\n";
	cout << "Email                   :   maosokveasna48@gmail.com\n";
	cout << "Component code and name :   GD1P02 - Algorithms and Data Structures\n";
	cout << "Name					 :   Assessment 2\n";
	cout << "Description             :   Implement graph algorithm\n\n";
	cout << "**************************************************************************\n\n";
}

/*==================Run========================*/
void GraphManager::Run()
{
	try {
		int searchChoice = -1;
		while (searchChoice != 0) {
			MainMenu();
			searchChoice = Validation::ValidateIntInput("Enter choice: ", 0, 8);
			ClearScreen();

			switch (searchChoice) {
			case 1: LoadMapFromFile(); break;
			case 2: DisplayMap(); break;
			case 3: LoadGraphFromMap(); break;
			case 4: DisplayGraph(); break;
			case 5: RunDFS(); break;
			case 6: RunBFS(); break;
			case 7: RunAStar(); break;
			case 8: SaveAStarPath(); break;
			case 0: cout << "Exiting program..." << endl; exit(0);
			default: cout << "Invalid input. Please try again." << endl;
			}
		}
	}
	catch (exception& e) {
		cout << "Run error: " << e.what() << endl;
		return;
	}

}
