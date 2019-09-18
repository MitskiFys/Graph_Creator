#include <iostream>
#include "Graph.h"
#include "Matrix.h"
using namespace std;

int main()
{

	Matrix mat(5);
	mat.AddBidirectionalEdge(1, 3, 5);
	mat.AddDirectionalEdge(2, 4, 3);
	cout << mat.GetDistanceBetweenNods(2, 4) << endl;
	//cout << mat.GetDistanceBetweenNods(3, 1);
	mat.DrawMatrix();
	cout << endl;
	mat.AddNode();
	mat.DrawMatrix();
	cout << endl;
	mat.DeleteNode(3);
	mat.DrawMatrix();
	cout << endl;
	mat.AddNode();
	mat.DrawMatrix();

	/*Graph first(5);
	first.AddDirectionalEdge(2, 3, 5);
	first.GetAdjacencyMatrix();*/
}
