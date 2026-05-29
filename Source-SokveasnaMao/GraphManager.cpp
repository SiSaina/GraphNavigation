#include "GraphManager.h"

GraphManager::GraphManager()
{
	graphPtr = nullptr;
}

GraphManager::~GraphManager()
{
	if (graphPtr != nullptr) {
		delete graphPtr;
		graphPtr = nullptr;
	}
}


void GraphManager::LoadMap()
{
	try {
		FileMenu();
		int pathOption = Validation::ValidateIntInput("Enter option: ", 0, 2);
		if (pathOption == 0) return;

		string filePath;

		if (pathOption == 1) {
			cout << "Enter file path to load inventory: ";
			getline(cin, filePath);
		}
		else if (pathOption == 2) {
			filePath = "C:\\School\\Year 1 term 2\\Algorithm & Data Structure\\Assignment 2\\ExampleMaps\\ExampleMaps\\ValidMap1.txt";
		}

		if (!Validation::ValidateFilePath(filePath)) {
			cout << "LoadMap: fail to load map from " << filePath << endl;
			return;
		}
		if (!map.LoadFromFile(filePath, error)) {
			cout << "LoadMap error: " << error << endl;
			return;
		}
		cout << "Load map successfully from " << filePath << endl;
	}
	catch (exception& e) {
		cout << "Run error: " << e.what() << endl;
		return;
	}
}

void GraphManager::DisplayMap()
{
	try {
		map.Display();
	}
	catch (exception& e) {
		cout << e.what() << endl;
		return;
	}
}

void GraphManager::LoadGraph()
{
	try {
		if (!map.IsMapLoaded()) {
			cout << "LoadGraph: map not loaded" << endl;
			return;
		}
		graphPtr = GraphTools::GetGraphFromMap(&map);
		cout << "Graph loaded successfully from map" << endl;
	}
	catch (exception& e) {
		cout << e.what() << endl;
		return;
	}
}

void GraphManager::DisplayGraph() {
	try {
		GraphTools::Display(graphPtr);
		// GraphTools::PrintAllNodeDistances(&map);
	}
	catch (exception& e) {
		cout << e.what() << endl;
		return;
	}
}

void GraphManager::DFS()
{
	try {
		GraphTools::DFS(graphPtr, 's'); // assuming 's' exists
	}
	catch (exception& e) {
		cout << e.what() << endl;
		return;
	}
}

void GraphManager::BFS()
{
	try {
		GraphTools::BFS(graphPtr, 's'); // assuming 's' exists
	}
	catch (exception& e) {
		cout << e.what() << endl;
		return;
	}
}

void GraphManager::FileMenu()
{
	cout << "1. Specific path" << endl;
	cout << "2. Default" << endl;
	cout << "0. Back" << endl;
}

void GraphManager::MainMenu()
{
	cout << "------Main Menu-------" << endl;
	cout << "1. Load Map from file" << endl;
	cout << "2. Display Map" << endl;
	cout << "3. Load Graph from Map" << endl;
	cout << "4. Display Graph" << endl;
	cout << "5. Run DFS" << endl;
	cout << "6. Run BFS" << endl;
	cout << "0. Exit" << endl;
}
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
void GraphManager::Run()
{
	try {
		int searchChoice = -1;
		while (searchChoice != 0) {
			MainMenu();
			searchChoice = Validation::ValidateIntInput("Enter choice: ", 0, 6);

			switch (searchChoice) {
			case 1:
				LoadMap();
				break;
			case 2:
				DisplayMap();
				break;
			case 3:
				LoadGraph();
				break;
			case 4:
				DisplayGraph();
				break;
			case 5:
				DFS();
				break;
			case 6:
				BFS();
				break;
			case 0:
				cout << "Exiting program..." << endl;
				exit(0);
			default:
				cout << "Invalid input. Please try again." << endl;
			}
		}
	}
	catch (exception& e) {
		cout << "Run error: " << e.what() << endl;
		return;
	}

}
