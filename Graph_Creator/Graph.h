#pragma once
#include <vector>
#include <iostream>
#include "Matrix.h"

using namespace std;

class Graph
{
private:
	vector <vector<int>>AdjacencyMatrix;//Матрица смежности
	vector <vector<int>>IncidenceMatrix;//Матрица инцидентности
	vector <int>ShortestWay;
	int CountOfNods = 0;
public:
	Graph();//Граф с неизвестным количеством вершин(задается далее) 
	Graph(int);//Граф с заранее известным количеством вершин (колчество вершин)
	void AddNode();//Добавить вершину
	void DeleteNode(int);//Удлаить вершину (номер вершины)
	void AddDirectionalEdge(int, int, int);//Добавить направленное ребро (начало, конец, длина)
	void AddBidirectionalEdge(int, int, int);//Добавить двунаправленное ребро (начало, конец, длина) 
	void DeleteEdge(char);//удалить ребро (регистр ребра из буквенного алфавита)
	void GetAdjacencyMatrix();//Вывод матрицы
};

