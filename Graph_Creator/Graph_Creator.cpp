#include <iostream>
#include "Graph.h"
#include "Matrix.h"
using namespace std;

int main()
{
	Graph grp(5);
	grp.AddDirectionalEdge(1, 3, 4);
	grp.GetAdjacencyMatrix();
	grp.GetIncidenceMatrix();
}
