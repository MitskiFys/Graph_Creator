#include <iostream>
#include "Graph.h"
using namespace std;

int main()
{
	vector <vector<int>>line;
	vector <int>ShortestWay;
	vector <int> length;
	for (int i = 0; i < 3; i++) {
		length.push_back(i + 1);
	}
	line.push_back(length);
	for (int i = 0; i < 3; i++) {
		length[i] = i+2;
	}
	line.push_back(length);
	cout << line[1][2];

	cout << "Hello World!" << endl;
}
