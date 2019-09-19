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
	int NumberOfNods = 0;


public:
	Matrix();
	Matrix(int);
	Matrix(int, int);//столбики, строки

	void AddDirectionalEdge(int, int, int);//Добавить направленное ребро (начало, конец, длина)
	void AddBidirectionalEdge(int, int, int);//Добавить двунаправленное
	const int GetDistanceBetweenNods(int, int);//Получить расстояние между вершинами
	void AddNode();//Добавить вершину
	void AddColumn();// Добавить колонку
	void AddRow();// Добавить строчку
	void DeleteNode(int);// Удлаить вершину (номер вершины)
	void DeleteColumn(int);//Удалть колонку
	void DeleteRow(int);// Удалить строчку
	void DrawMatrix();// Вывести матрицу 
	int GetFirstIndexRow();// Получить первый индекс строки
	int GetLastIndexColumn();//Получить индекс последнего вставленной строки
	int GetCountOfColumns();// Получить количество колонок
	bool IssetRow(int);// Проверить на существование строки
	bool IssetColumn(int);// Проверить на существование колонки
};

