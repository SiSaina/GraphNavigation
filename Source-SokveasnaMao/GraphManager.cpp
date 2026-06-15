/***************************************************************************
Bachelor of Software Engineering
Media Design School
Auckland, New Zealand
(c) Year 1 Media Design School

Author                  : Sokveasna Mao
Email                   : maosokveasna48@gmail.com
Component code and name : GD1P02 - Algorithms and Data Structures
Name                    : Assessment 2

File                    : GraphManager.cpp

Description:
	Implementation of GraphManager class
***************************************************************************/

#include "GraphManager.h"

/*==================Graph Manager constructor========================*/
GraphManager::GraphManager()
{
	graphList = nullptr;
}

/*==================Graph Manager destructor========================*/
GraphManager::~GraphManager()
{
	if (graphList != nullptr) {
		delete graphList;
		graphList = nullptr;
	}
}

/*==================Load Map From File========================*/
void GraphManager::LoadMapFromFile()
{
	try {
		DisplayFileMenu();
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
			filePath = SelectDefaultMap();

			if (filePath.empty()) return;
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
		CleanGraph();
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
		// check map is loaded or not
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

		graphList = GraphTools::GetGraphFromMap(&map);
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
		GraphTools::DisplayGraphList(graphList);
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
		GraphTools::DFS(graphList, 's'); // assuming 's' exists
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
		GraphTools::BFS(graphList, 's'); // assuming 's' exists
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

		// initial the start and exit position
		int startRow, startCol, exitRow, exitCol;
		map.SetStartPosition(startRow, startCol);
		map.SetExitPosition(exitRow, exitCol);
	
		// perform A* core function
		bool found = pathFinder.FindPath(&map, { startRow, startCol }, { exitRow, exitCol });

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

void GraphManager::DisplayAStarPath()
{
	try {
		if (!GraphReady()) {
			cout << "DisplayGraph: graph is not ready to display" << endl;
			return;
		}
		// check if path have been found or not
		if (!pathFinder.PathFound()) {
			cout << "DisplayAStarPath: no path available. Run A* first" << endl;
			return;
		}

		pathFinder.DisplayPath(&map);
	}
	catch (exception& e) {
		cout << "DisplayGraph error: " << e.what() << endl;
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

		// specified the file location (default or specific)
		cout << "File menu" << endl;
		DisplayFileMenu();
		int choice = Validation::ValidateIntInput("Enter choice: ", 0, 2);

		switch (choice) {
		// specific file path
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
		// default path
		case 2: {
			string defaultFile = "AStar\\pathOutput.txt";
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

	if (graphList == nullptr) {
		cout << "No graph loaded.\n";
		return false;
	}

	return true;
}

/*==================Clean Grpah========================*/
bool GraphManager::CleanGraph()
{
	if (graphList != nullptr) {
		delete graphList;
		graphList = nullptr;
		return true;
	}
	return false;
}

string GraphManager::SelectDefaultMap()
{
	vector<string> maps =
	{
		"Map\\ValidMap1.txt",
		"Map\\ValidMap2.txt",
		"Map\\InvalidMap1.txt",
		"Map\\InvalidMap2.txt",
		"Map\\InvalidMap3.txt",
		"Map\\InvalidMap4.txt",
		"Map\\InvalidMap5.txt",
		"Map\\ValidMapNoPath1.txt",
		"Map\\ValidMapNoPath2.txt"
	};

	for (int i = 0;i < maps.size(); i++) {
		cout << i + 1 << ". " << maps[i] << endl;
	}
	cout << "0. Cancel" << endl;
	int mapChoice = Validation::ValidateIntInput("Select map: ", 0, maps.size());

	if (mapChoice == 0) return "";

	return maps[mapChoice - 1];
}

/*==================Clear Screen========================*/
void GraphManager::ClearScreen()
{
	system("cls");
	DisplayMDSHeader();
}

/*==================File Menu========================*/
void GraphManager::DisplayFileMenu()
{
	cout << "1. Specific path" << endl;
	cout << "2. Default" << endl;
	cout << "0. Back" << endl;
}

/*==================DisplayMainMenu========================*/
void GraphManager::DisplayMainMenu()
{
	cout << endl;
	cout << "------Main Menu-------" << endl;
	cout << "1. Load Map from file" << endl;
	cout << "2. Load Graph from Map" << endl;
	cout << "3. Display Map" << endl;
	cout << "4. Display Graph" << endl;
	cout << "5. Run DFS" << endl;
	cout << "6. Run BFS" << endl;
	cout << "7. Run AStar" << endl;
	cout << "8. Display AStar" << endl;
	cout << "9. Save AStar Path" << endl;
	cout << "0. Exit" << endl;
}
/*==================DisplayMDSHeader========================*/
void GraphManager::DisplayMDSHeader() {
	cout << "***********************************************************************\n\n";
	cout << "Bachelor of Software Engineering\n";
	cout << "Media Design School\n";
	cout << "Auckland,    New Zealand\n";
	cout << "(c) Year 1 Media Design School\n\n";
	cout << "Author                  :   Sokveasna Mao\n";
	cout << "Email                   :   maosokveasna48@gmail.com\n";
	cout << "Component code and name :   GD1P02 - Algorithms and Data Structures\n";
	cout << "Name                    :   Assessment 2\n";
	cout << "Description             :   Implement graph algorithm\n\n";
	cout << "**************************************************************************\n\n";
}

/*==================Run========================*/
void GraphManager::Run()
{
	try {
		int searchChoice = -1;
		while (searchChoice != 0) {
			DisplayMainMenu();
			searchChoice = Validation::ValidateIntInput("Enter choice: ", 0, 9);
			ClearScreen();

			switch (searchChoice) {
			case 1: LoadMapFromFile(); break;
			case 2: LoadGraphFromMap(); break;
			case 3: DisplayMap(); break;
			case 4: DisplayGraph(); break;
			case 5: RunDFS(); break;
			case 6: RunBFS(); break;
			case 7: RunAStar(); break;
			case 8: DisplayAStarPath(); break;
			case 9: SaveAStarPath(); break;
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
