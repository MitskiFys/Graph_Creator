#ifndef MATRIX_H
#define MATRIX_H
#pragma once
#include <map>
#include <iostream>

using namespace std;
class Matrix
{
private:
    typedef multimap <int, int> mapintint;
    typedef multimap <int, mapintint> mapintmap;

    mapintmap MyMatrix;// Матрица
    mapintint::iterator IterLine;
    mapintmap::iterator IterColumn;
    int NumberOfNods = 0;

public:
    Matrix();
    Matrix(int);
    Matrix(int, int);//столбики, строки

    void AddDirectionalEdge(int, int, int);//Добавить направленное ребро (начало, конец, длина)
    void AddBidirectionalEdge(int, int, int);//Добавить двунаправленное
    int GetDistanceBetweenNods(int, int);//Получить расстояние между вершинами
    void AddNode();//Добавить вершину
    void AddColumn();// Добавить колонку
    void AddColumn(int);
    void AddRow();// Добавить строчку
    void DeleteNode(int);// Удлаить вершину (номер вершины)
    void DeleteColumn(int);//Удалть колонку
    void DeleteRow(int);// Удалить строчку
    void DrawMatrix();// Вывести матрицу
    int GetFirstIndexRow();// Получить первый индекс строки
    int GetLastIndexRow();
    int GetFirstIndexColumn();
    int GetLastIndexColumn();//Получить индекс последнего вставленной строки
    int GetCountOfRows();// Получить количество строк
    int GetCountOfColumns();//Получить количество колонок
    bool IssetRow(int);// Проверить на существование строки
    bool IssetColumn(int);// Проверить на существование колонки
    void SetCell(int, int, int);

    const int& operator()(int&, int&);
};


#endif // MATRIX_H
