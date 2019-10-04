#ifndef GRAPH_H
#define GRAPH_H
#pragma once
#include <vector>
#include <iostream>
#include "Matrix.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <graphviz/gvc.h>
#include <fstream>
#include <string>
#include <iostream>
#include <QStringList>

using namespace std;

class Graph
{
private:
    Matrix AdjacencyMatrix;//Матрица смежности
    Matrix IncidenceMatrix;//Матрица инцидентности
    vector <int> ShortestWay;//Кротчайший путь
    vector <int> Length;//Расстояние
    int CountOfNods = 0;//Количество вершин
    string AddedNods = "";//Список добавленных вершин
public:
    QStringList Headers;//Оглавления
    Graph();//Граф с неизвестным количеством вершин(задается далее)
    Graph(int);//Граф с заранее известным количеством вершин (колчество вершин)
    void AddNode();//Добавить вершину
    void DeleteNode(int);//Удлаить вершину (номер вершины)
    void AddDirectionalEdge(int, int, int);//Добавить направленное ребро (начало, конец, длина)
    void AddBidirectionalEdge(int, int, int);//Добавить двунаправленное ребро (начало, конец, длина)
    void DeleteEdge(int);//удалить ребро
    void GetAdjacencyMatrix();//Вывод матрицы смежности
    void GetIncidenceMatrix();//Вывод матрицы инцидентности
    void GetDotFile();//Получить DOT файл
    void GetDotFile(int, int);//Получить DOT файл с кротчайшим путем
    int GetEdgeIndex(int,int);//Получиь индекс ребра соединяющий 2 вершины
    void AddHeader(int);//Добавить оглавление
    void DeleteHeader(int);//Удалить оглавление
    void RunAlgoDijkstra(int);//Запустить алгоритм Дейкстры с вершины
    bool IsEdgeBiDirectional(int,int,int);//Проверить на двунапревленность ребро
    int GetIndexFromHeader(int);//Получить индекс оглавления
};
#endif // GRAPH_H
