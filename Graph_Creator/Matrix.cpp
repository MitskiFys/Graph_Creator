#include "Matrix.h"

Matrix::Matrix()
{
}

Matrix::Matrix(int Count):NumberOfNods(Count)
{

	for (int i = 0; i < NumberOfNods; i++) {
		for (int j = 0; j < NumberOfNods; j++) {
			Row.insert(pair<int, int>(j, 0));
		}
		Column.insert(pair<int, mapintint>(i, Row));
		Row.clear();
	}

}

Matrix::Matrix(int ColumnCount, int RowCount)
{
	for (int i = 0; i < RowCount; i++) {
		for (int j = 0; j < ColumnCount; j++) {
			Row.insert(pair<int, int>(j, 0));
		}
		Column.insert(pair<int, mapintint>(i, Row));
		Row.clear();
	}

}

void Matrix::AddDirectionalEdge(int FirstNode, int SecondNode, int Length)
{
	(*(*Column.find(FirstNode - 1)).second.find(SecondNode - 1)).second = Length;
}

void Matrix::AddBidirectionalEdge(int FirstNode, int SecondNode, int Length)
{
	AddDirectionalEdge(FirstNode, SecondNode, Length);
	AddDirectionalEdge(SecondNode, FirstNode, Length);
}

const int Matrix::GetDistanceBetweenNods(int FirstNode, int SecondNode)
{
	return (*(*Column.find(FirstNode - 1)).second.find(SecondNode - 1)).second;
}

void Matrix::AddNode()
{
	if (GetCountOfColumns() != 0)
		AddRow();
	AddColumn();
	
}

void Matrix::AddColumn()
{
	if (Column.begin() != Column.end()) {
		for (IterColumn = Column.begin(); IterColumn != Column.end(); ++IterColumn) {
			(*IterColumn).second.insert(pair<int, int>((*(--(*Column.begin()).second.end())).first + 1, 0));
		}
	}
	else {
		Row.insert(pair<int, int>(0, 0));
		Column.insert(pair<int, mapintint>(0, Row));
	}
}

void Matrix::AddRow()
{
	if (Column.begin() != Column.end()) {
		Row.clear();
		for (IterLine = (*Column.begin()).second.begin(); IterLine != (*Column.begin()).second.end(); ++IterLine) {
			Row.insert(pair<int, int>((*IterLine).first, 0));
		}
		Column.insert(pair<int, mapintint>(((*--Column.end()).first) + 1, Row));
	}
	else {
		Row.insert(pair<int, int>(0, 0));
		Column.insert(pair<int, mapintint>(0, Row));
	}
	
}

void Matrix::DeleteNode(int Number)
{
	DeleteColumn(Number);
	DeleteRow(Number);
}

void Matrix::DeleteColumn(int Number)
{
	for (IterColumn = Column.begin(); IterColumn != Column.end(); ++IterColumn) {
		(*IterColumn).second.erase(Number - 1);
	}
}

void Matrix::DeleteRow(int Number)
{
	Column.erase(Number - 1);
}

void Matrix::DrawMatrix()
{
	cout << "  ";
	if (Column.begin() != Column.end()) {
		for (IterLine = (*Column.begin()).second.begin(); IterLine != (*Column.begin()).second.end(); ++IterLine) {
			cout << (*IterLine).first + 1 << ' ';
		}
		cout << endl;
		for (IterColumn = Column.begin(); IterColumn != Column.end(); ++IterColumn) {
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
	if (Column.begin() != Column.end()) {
		return (*Column.begin()).first + 1;
	}
	else {
		return 0;
	}
}

int Matrix::GetLastIndexColumn()
{
	return (*--Column.end()).first + 1;
}

int Matrix::GetCountOfColumns()
{
	return 	Column.size();
}

bool Matrix::IssetRow(int Number)
{
	mapintmap it;
	if (Column.find(Number - 1) != Column.end()) {
		return true;
	}
	else {
		return false;
	}
}

bool Matrix::IssetColumn(int Number)
{
	IterLine = (*Column.begin()).second.find(Number - 1);
	(*Column.begin()).second.end();
	if (IterLine != (*Column.begin()).second.end()) {
		return true;
	}
	return false;
}


