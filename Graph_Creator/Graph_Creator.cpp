#include <iostream>
#include "Graph.h"
#include <map>
using namespace std;

int main()
{
	Graph first(5);
	first.AddDirectionalEdge(2, 3, 5);
	first.GetAdjacencyMatrix();
}
