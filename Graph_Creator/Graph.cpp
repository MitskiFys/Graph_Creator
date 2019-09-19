#include "Graph.h"

Graph::Graph()
{

}

Graph::Graph(int Number)
{
	for (int i = 0; i < Number; i++) {
		AdjacencyMatrix.AddNode();
		IncidenceMatrix.AddColumn();
	}
}

void Graph::AddNode()
{
	AdjacencyMatrix.AddNode();
}

void Graph::DeleteNode(int Number)
{
	AdjacencyMatrix.DeleteNode(Number);
	IncidenceMatrix.DeleteColumn(Number);
}

void Graph::AddDirectionalEdge(int FirstNode, int SecondNode, int Length)
{
	AdjacencyMatrix.AddDirectionalEdge(FirstNode, SecondNode, Length);
	if (IncidenceMatrix.GetCountOfColumns() == 0) {
		for (int i = 0; i < AdjacencyMatrix.GetCountOfColumns(); i++) {
			IncidenceMatrix.AddColumn();
		}
	}
	else {
		IncidenceMatrix.AddRow();
	}
	IncidenceMatrix.AddDirectionalEdge(IncidenceMatrix.GetLastIndexColumn(), FirstNode, 1);
	IncidenceMatrix.AddDirectionalEdge(IncidenceMatrix.GetLastIndexColumn(), SecondNode, -1);
}

void Graph::AddBidirectionalEdge(int FirstNode, int SecondNode, int Length)
{
	AdjacencyMatrix.AddBidirectionalEdge(FirstNode, SecondNode, Length);
	if (IncidenceMatrix.GetCountOfColumns() == 0) {
		for (int i = 0; i < AdjacencyMatrix.GetCountOfColumns(); i++) {
			IncidenceMatrix.AddColumn();
		}
	}
	else {
		IncidenceMatrix.AddRow();
	}
	IncidenceMatrix.AddDirectionalEdge(IncidenceMatrix.GetLastIndexColumn(), FirstNode, -1);
	IncidenceMatrix.AddDirectionalEdge(IncidenceMatrix.GetLastIndexColumn(), SecondNode, -1);
}

void Graph::DeleteEdge(int Number)
{
		
}

void Graph::GetAdjacencyMatrix()
{
	AdjacencyMatrix.DrawMatrix();
}

void Graph::GetIncidenceMatrix()
{
	IncidenceMatrix.DrawMatrix();
}


