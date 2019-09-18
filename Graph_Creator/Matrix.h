#pragma once
#include <map>
#include <iostream>

using namespace std;
class Matrix
{
private:
	typedef multimap <int, int> mapintint;
	typedef multimap <int, mapintint> mapintmap;
	mapintint Row;// Строка
	mapintmap Column;// Столбец
	mapintint::iterator IterLine;
	mapintmap::iterator IterColumn;
	int NumberOfNods;


public:

	Matrix(int);

	void AddDirectionalEdge(int, int, int);//Добавить направленное ребро (начало, конец, длина)
	void AddBidirectionalEdge(int, int, int);//Добавить двунаправленное
	const int GetDistanceBetweenNods(int, int);//ПОлучить расстояние между вершинами
	void AddNode();//Добавить вершину
	void DeleteNode(int);//Удлаить вершину (номер вершины)
	void DrawMatrix();
};

