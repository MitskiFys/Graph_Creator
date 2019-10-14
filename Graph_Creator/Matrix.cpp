#include "Matrix.h"

Matrix::Matrix()
{
}

Matrix::Matrix(int Count):NumberOfNods(Count)
{
    mapintint Row;// Строка
    for (int i = 0; i < NumberOfNods; i++) {
        for (int j = 0; j < NumberOfNods; j++) {
            Row.insert(pair<int, int>(j, 0));
        }
        MyMatrix.insert(pair<int, mapintint>(i, Row));
        Row.clear();
    }

}

Matrix::Matrix(int ColumnCount, int RowCount)
{
    mapintint Row;// Строка
    for (int i = 0; i < RowCount; i++) {
        for (int j = 0; j < ColumnCount; j++) {
            Row.insert(pair<int, int>(j, 0));
        }
        MyMatrix.insert(pair<int, mapintint>(i, Row));
        Row.clear();
    }

}

void Matrix::AddDirectionalEdge(int FirstNode, int SecondNode, int Length)
{
    (*(*MyMatrix.find(FirstNode - 1)).second.find(SecondNode - 1)).second = Length;
}

void Matrix::AddBidirectionalEdge(int FirstNode, int SecondNode, int Length)
{
    AddDirectionalEdge(FirstNode, SecondNode, Length);
    AddDirectionalEdge(SecondNode, FirstNode, Length);
}

const int Matrix::GetDistanceBetweenNods(int FirstNode, int SecondNode)
{
    return (*(*MyMatrix.find(FirstNode - 1)).second.find(SecondNode - 1)).second;
}

void Matrix::AddNode()
{
    if (GetCountOfRows() != 0)
        AddRow();
    AddColumn();

}

void Matrix::AddColumn()
{
    mapintint Row;// Строка
    if (MyMatrix.begin() != MyMatrix.end()) {
        for (IterColumn = MyMatrix.begin(); IterColumn != MyMatrix.end(); ++IterColumn) {
            (*IterColumn).second.insert(pair<int, int>((*(--(*IterColumn).second.end())).first + 1, 0));
        }
    }

    else {
        Row.insert(pair<int, int>(0, 0));
        MyMatrix.insert(pair<int, mapintint>(0, Row));
    }
}

void Matrix::AddColumn(int index)
{
    mapintint Row;// Строка
    if (MyMatrix.begin() != MyMatrix.end()) {
        for (IterColumn = MyMatrix.begin(); IterColumn != MyMatrix.end(); ++IterColumn) {
            (*IterColumn).second.insert(pair<int, int>((*(--(*IterColumn).second.end())).first + 1, 0));
        }
    }

    else {
        Row.insert(pair<int, int>(index - 1, 0));
        MyMatrix.insert(pair<int, mapintint>(0, Row));
    }
}

void Matrix::AddRow()
{
    mapintint Row;// Строка
    if (MyMatrix.begin() != MyMatrix.end()) {
        Row.clear();
        for (IterLine = (*MyMatrix.begin()).second.begin(); IterLine != (*MyMatrix.begin()).second.end(); ++IterLine) {
            Row.insert(pair<int, int>((*IterLine).first, 0));
        }
        MyMatrix.insert(pair<int, mapintint>(((*--MyMatrix.end()).first) + 1, Row));
    }
    else {
        Row.insert(pair<int, int>(0, 0));
        MyMatrix.insert(pair<int, mapintint>(0, Row));
    }

}

void Matrix::DeleteNode(int Number)
{
    DeleteColumn(Number);
    DeleteRow(Number);

}

void Matrix::DeleteColumn(int Number)
{
    for (IterColumn = MyMatrix.begin(); IterColumn != MyMatrix.end(); ++IterColumn) {
        (*IterColumn).second.erase(Number - 1);
    }
}

void Matrix::DeleteRow(int Number)
{
    int n = (MyMatrix.find(Number-1))->first;
    MyMatrix.erase(n);
}

void Matrix::DrawMatrix()
{
    cout << "  ";
    if (MyMatrix.begin() != MyMatrix.end()) {
        for (IterLine = (*MyMatrix.begin()).second.begin(); IterLine != (*MyMatrix.begin()).second.end(); IterLine++) {
            cout << (*IterLine).first + 1 << ' ';
        }
        cout << endl;
        for (IterColumn = MyMatrix.begin(); IterColumn != MyMatrix.end(); IterColumn++) {
            cout << (*IterColumn).first + 1 << ' ';
            for (IterLine = (*IterColumn).second.begin(); IterLine != (*IterColumn).second.end(); ++IterLine) {
                cout << (*IterLine).second << " ";
            }
            cout << endl;
        }
    }

}

int Matrix::GetFirstIndexRow()
{
    if (MyMatrix.begin() != MyMatrix.end()) {
        return (*MyMatrix.begin()).first + 1;
    }
    else {
        return 0;
    }
}

int Matrix::GetLastIndexRow()
{
    if (MyMatrix.begin() != MyMatrix.end()) {
        return (*(--MyMatrix.end())).first + 1;
    }
    else {
        return 0;
    }

}

int Matrix::GetFirstIndexColumn()
{
    return (*(*MyMatrix.begin()).second.begin()).first+1;
}

int Matrix::GetLastIndexColumn()
{
    return (*--(*MyMatrix.begin()).second.end()).first+1;}

int Matrix::GetCountOfRows()
{
    return 	MyMatrix.size();
}

int Matrix::GetCountOfColumns()
{

    return (*MyMatrix.begin()).second.size();
}

bool Matrix::IssetRow(int Number)
{
    mapintmap it;
    if (MyMatrix.find(Number - 1) != MyMatrix.end()) {
        return true;
    }
    else {
        return false;
    }
}

bool Matrix::IssetColumn(int Number)
{
    IterLine = (*MyMatrix.begin()).second.find(Number - 1);
    if (IterLine != (*MyMatrix.begin()).second.end()) {
        return true;
    }
    return false;
}

const int& Matrix::operator()(int& Row, int& Column)
{
    return (*(*this->MyMatrix.find(Row - 1)).second.find(Column - 1)).second;
}
