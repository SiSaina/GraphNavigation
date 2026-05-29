#include "GraphList.h"

void GraphList::InsertNode(int label)
{
	if (NodeExists(label)) throw "Node already exist";

	nodeIndices[label] = maxIndex;
	nodeLabels[maxIndex] = label;

	vector<pair<int, double>> newVector;
	adjList.push_back(newVector);
	maxIndex++;
}

void GraphList::Connect(int nodeA, int nodeB, double weight) {
	if (!NodeExists(nodeA) || !NodeExists(nodeB)) throw "Node does not exist";

	if (AreConnected(nodeA, nodeB)) return;

	int indexA = nodeIndices[nodeA];
	int indexB = nodeIndices[nodeB];

	adjList[indexA].push_back({ indexB, weight });

	// reverse connect
	adjList[indexB].push_back({ indexA, weight });
}

bool GraphList::AreConnected(int nodeA, int nodeB) {
	if (!NodeExists(nodeA) || !NodeExists(nodeB)) throw "Node does not exist";
	
	int indexA = nodeIndices[nodeA];
	int indexB = nodeIndices[nodeB];

	for (pair<int, double> neighbour : adjList[indexA]) {
		if (neighbour.first == indexB) return true;
	}
	return false;
}

vector<pair<int, double>> GraphList::GetNeighbourList(int node)
{
	int index = nodeIndices[node];

	vector<pair<int, double>> result;
	result.reserve(adjList[index].size());

	for (const pair<int, double>& edge : adjList[index]) {
		int label = nodeLabels[edge.first]; // index -> label
		result.push_back({ label, edge.second });
	}

	return result;
}