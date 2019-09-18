#include "Matrix.h"

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

void Matrix::AddDirectionalEdge(int FirstNode, int SecondNode, int Length)
{
	(*(*Column.find(FirstNode - 1)).second.find(SecondNode - 1)).second = Length;
}

void Matrix::AddBidirectionalEdge(int FirstNode, int SecondNode, int Length)
{
	(*(*Column.find(FirstNode - 1)).second.find(SecondNode - 1)).second = Length;
	(*(*Column.find(SecondNode - 1)).second.find(FirstNode - 1)).second = Length;

}

const int Matrix::GetDistanceBetweenNods(int FirstNode, int SecondNode)
{
	return (*(*Column.find(FirstNode - 1)).second.find(SecondNode - 1)).second;
}

void Matrix::AddNode()
{
	Row.clear();
	for (IterColumn = Column.begin(); IterColumn != Column.end(); ++IterColumn) {
		(*IterColumn).second.insert(pair<int, int>(((*--Column.end()).first)+1, 0));
	}
	for (IterLine = (*Column.begin()).second.begin(); IterLine != (*Column.begin()).second.end(); ++IterLine) {
		Row.insert(pair<int, int>((*IterLine).first, 0));
	}
	Column.insert(pair<int, mapintint>(((*--Column.end()).first) + 1, Row));
}

void Matrix::DeleteNode(int Number)
{
	Column.erase(Number - 1);
	for (IterColumn = Column.begin(); IterColumn != Column.end(); ++IterColumn) {
		(*IterColumn).second.erase(Number-1);
	}
}

void Matrix::DrawMatrix()
{
	cout << "  ";
	for (IterLine = (*Column.begin()).second.begin(); IterLine != (*Column.begin()).second.end(); ++IterLine) {
		cout << (*IterLine).first+1 << ' ';
	}
	cout << endl;
	for (IterColumn = Column.begin(); IterColumn != Column.end(); ++IterColumn) {
		cout << (*IterColumn).first+1 << ' ';
		for (IterLine = (*IterColumn).second.begin(); IterLine != (*IterColumn).second.end(); ++IterLine) {
			cout << (*IterLine).second << " ";
		}
		cout << endl;
	}
}