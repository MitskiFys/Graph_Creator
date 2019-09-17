#include "Graph.h"

Graph::Graph()
{

}

Graph::Graph(int count)
{
	CountOfNods = count;
	for (int i = 0; i < CountOfNods; i++) {
		vector <int> column;
		for (int j = 0; j < CountOfNods; j++) {
			column.push_back(0);
		}
		AdjacencyMatrix.push_back(column);
	}
}

void Graph::AddNode()
{

}

void Graph::DeleteNode(int)
{
}

void Graph::AddDirectionalEdge(int first, int second, int length)
{
	AdjacencyMatrix[second - 1][first - 1] = length;
}

void Graph::AddBidirectionalEdge(int, int, int)
{
}

void Graph::DeleteEdge(char)
{
}

void Graph::GetAdjacencyMatrix()
{
	cout << "  ";
	for (int i = 0; i < CountOfNods; i++) {
		cout << i+1 << " ";
	}
	cout << endl;
	for (int i = 0; i < CountOfNods; i++) {
		cout << i+1 << " ";
		for (int j = 0; j < CountOfNods; j++) {
			cout << AdjacencyMatrix[j][i] << ' ';
		}
		cout << endl;
	}
}
