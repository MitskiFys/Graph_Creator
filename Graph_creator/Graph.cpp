#include <Graph.h>
Graph::Graph()
{


}

Graph::Graph(int Number)
{
    for (int i = 0; i < Number; i++) {
        AdjacencyMatrix.AddNode();
    }
}

void Graph::AddNode()
{
    AdjacencyMatrix.AddNode();
    if (IncidenceMatrix.GetCountOfRows()!=0){
        IncidenceMatrix.AddColumn();
    }
}

void Graph::DeleteNode(int Number)
{
    //AdjacencyMatrix.DrawMatrix();
    vector <int> NumberToDelete;
    for (int i = IncidenceMatrix.GetFirstIndexRow(); i <=IncidenceMatrix.GetLastIndexRow()+1;i++){
        if ((IncidenceMatrix.IssetRow(i))&&(IncidenceMatrix(i,Number)!=0)) {
            NumberToDelete.push_back(i);//5,6,10,14,
        }
    }
    //for (vector <int>::iterator iter = NumberToDelete.begin(); iter!=NumberToDelete.end();iter++){
    for (auto iter: NumberToDelete){
        //cout << IncidenceMatrix.IssetRow(3);
        DeleteEdge(iter);
    }//Проверить удаления из списка
    AdjacencyMatrix.DeleteNode(Number);
    IncidenceMatrix.DeleteColumn(Number);
    IncidenceMatrix.DrawMatrix();
}

void Graph::AddDirectionalEdge(int FirstNode, int SecondNode, int Length)
{
    string Nods = to_string(FirstNode) + "with" + to_string(SecondNode);
    AdjacencyMatrix.AddDirectionalEdge(FirstNode, SecondNode, Length);
    if (IncidenceMatrix.GetCountOfRows() == 0) {
        for (int i = AdjacencyMatrix.GetFirstIndexRow(); i <= AdjacencyMatrix.GetLastIndexRow(); i++) {
            IncidenceMatrix.AddColumn(i);
        }
    }
    else {
        if (AddedNods.find(Nods)==std::string::npos){
            IncidenceMatrix.AddRow();
        }
    }

    if (AddedNods.find(Nods)==std::string::npos){
        IncidenceMatrix.AddDirectionalEdge(IncidenceMatrix.GetLastIndexRow(), FirstNode, 1);
        IncidenceMatrix.AddDirectionalEdge(IncidenceMatrix.GetLastIndexRow(), SecondNode, -1);
        AddedNods =AddedNods + to_string(FirstNode) + "with" + to_string(SecondNode)+"-"+to_string(IncidenceMatrix.GetLastIndexRow())+"-";
    }
}

void Graph::AddBidirectionalEdge(int FirstNode, int SecondNode, int Length)
{
    string Nods = to_string(FirstNode) + "with" + to_string(SecondNode);
    AdjacencyMatrix.AddBidirectionalEdge(FirstNode, SecondNode, Length);
    if (Length != 0){
        if (IncidenceMatrix.GetCountOfRows() == 0) {
            for (int i = AdjacencyMatrix.GetFirstIndexRow(); i <= AdjacencyMatrix.GetLastIndexRow(); i++) {
                IncidenceMatrix.AddColumn(i);
            }
        }
        else {
            if (AddedNods.find(Nods)==std::string::npos){
                IncidenceMatrix.AddRow();
            }
        }
        if (AddedNods.find(Nods)==std::string::npos){
            IncidenceMatrix.AddDirectionalEdge(IncidenceMatrix.GetLastIndexRow(), FirstNode, -1);
            IncidenceMatrix.AddDirectionalEdge(IncidenceMatrix.GetLastIndexRow(), SecondNode, -1);
            AddedNods =AddedNods + to_string(FirstNode) + "with" + to_string(SecondNode)+"-"+to_string(IncidenceMatrix.GetLastIndexRow())+"-";
        }
    }
}

void Graph::AddEdge()
{
    if (IncidenceMatrix.GetCountOfRows() == 0) {
        for (int i = AdjacencyMatrix.GetFirstIndexRow(); i <= AdjacencyMatrix.GetLastIndexRow(); i++) {
            IncidenceMatrix.AddColumn(i);
        }
    } else
        IncidenceMatrix.AddRow();
}

void Graph::DeleteEdge(int Number)
{
    int FirstNode = 0;
    int SecondNode = 0;
    //cout << IncidenceMatrix.IssetRow(3);
    for (int i = IncidenceMatrix.GetFirstIndexColumn(); i <= IncidenceMatrix.GetLastIndexColumn();i++) {
        if (IncidenceMatrix.IssetColumn(i))
            if (IncidenceMatrix(Number, i) != 0) {
                FirstNode = SecondNode;
                SecondNode = i;
            }
    }

    if (FirstNode==0)
        FirstNode = SecondNode;

    AdjacencyMatrix.AddBidirectionalEdge(FirstNode, SecondNode, 0);

    string Nods =to_string(FirstNode) + "with" + to_string(SecondNode)+"-"+to_string(Number)+"-";

    IncidenceMatrix.DeleteRow(Number);
    if (AddedNods.find(Nods)!= std::string::npos){
        AddedNods.erase(AddedNods.find(Nods),Nods.size());
    }else {
        string Nods =to_string(SecondNode) + "with" + to_string(FirstNode)+"-"+to_string(Number)+"-";
        if (AddedNods.find(Nods)!= std::string::npos){
            AddedNods.erase(AddedNods.find(Nods),Nods.size());
        }
    }
}

void Graph::GetAdjacencyMatrix()
{
    AdjacencyMatrix.DrawMatrix();
}

void Graph::GetIncidenceMatrix()
{
    IncidenceMatrix.DrawMatrix();
}

void Graph::CreateDotFile(int From , int To)
{
    DotFile = "";
    //std::ofstream outfile ("graph.dot");
    int FirtsNode = 0;
    int SecondNode = 0;
    int Direction = 1;
    DotFile += "digraph graphname {\n";
    DotFile += "graph [rankdir=LR] \n";//setting area https://graphviz.readthedocs.io/en/stable/manual.html
    map <int, int> Way;
    if ((From != 0)&&(To != 0))
        if (CheckShortestWayToValue(To))
            while (From != To){
                Way.insert(make_pair(To,ShortestWay[To]));
                To = ShortestWay[To];
            }
    for (int i = AdjacencyMatrix.GetFirstIndexRow(); i<= AdjacencyMatrix.GetLastIndexRow();i++){
        if (AdjacencyMatrix.IssetRow(i)){
            DotFile += to_string(i) + ";\n";
        }
    }
    for (int i = IncidenceMatrix.GetFirstIndexRow(); i <= IncidenceMatrix.GetLastIndexRow(); i++){
        if (IncidenceMatrix.IssetRow(i)){
            for (int j = IncidenceMatrix.GetFirstIndexColumn(); j<= IncidenceMatrix.GetLastIndexColumn();j++){
                if (IncidenceMatrix(i,j)==1){
                    FirtsNode = j;
                    Direction *= IncidenceMatrix(i,j);
                } else if (IncidenceMatrix(i,j)==-1){
                    if (FirtsNode == 0)
                        FirtsNode = SecondNode;
                    SecondNode = j;
                    Direction *= IncidenceMatrix(i,j);
                }
            }
            if ((FirtsNode == 0)&&(FirtsNode == SecondNode))
                continue;
            if (FirtsNode == 0){
                FirtsNode = SecondNode;
                Direction*=-1;
            }
            //cout << Way[SecondNode] << endl;
            if (!(((Way.find(SecondNode)!=Way.end())&&(Way[SecondNode]==FirtsNode)))){
                DotFile += to_string(FirtsNode);
                if (Direction < 0) {
                    DotFile += "->" + to_string(SecondNode) + " [label = " + to_string(AdjacencyMatrix(FirtsNode,SecondNode)) + "]\n";
                } else {
                    DotFile += "->" + to_string(SecondNode) + " [dir=\"both\",label = " + to_string(AdjacencyMatrix(FirtsNode,SecondNode)) + "]\n";
                }
                FirtsNode =0;
                SecondNode = 0;
                Direction = 1;
            } else {
                DotFile += to_string(FirtsNode);
                if (Direction < 0) {
                    DotFile += "->" + to_string(SecondNode) + " [color = Red, label = " + to_string(AdjacencyMatrix(FirtsNode,SecondNode)) + "]\n";
                } else {
                    DotFile += "->" + to_string(SecondNode) + " [dir=\"both\", color = Red, label = " + to_string(AdjacencyMatrix(FirtsNode,SecondNode)) + "]\n";
                }
                FirtsNode =0;
                SecondNode = 0;
                Direction = 1;
            }

        }

    }

    DotFile +="}\n";
}

int Graph::GetEdgeIndex(int FirstNode, int SecondNode)
{
    int Number = 0;
    string Nods = to_string(FirstNode) + "with" + to_string(SecondNode)+"-";
    if (AddedNods.find(Nods)!=std::string::npos){
        int start = AddedNods.find(Nods)+Nods.size();
        int end = AddedNods.find('-',AddedNods.find(Nods)+Nods.size());
        for (int i = start; i< end; i++){
            Number *=10;
            Number += (int)AddedNods[i]-48;
        }
    }
    return Number;
}

void Graph::AddHeader(int Node)
{
    QString Number = QString::number(Node);
    NodeHeaders << Number;
}

void Graph::DeleteHeader(int Node)
{
    QString Number =QString::number(Node);
    NodeHeaders.removeOne(Number);
}

void Graph::RunAlgoDijkstra(int From)
{
    if (GetIndexFromHeader(From)==-1){
        ShortestWay.clear();
        Length.clear();
        return;
    }
    int size = AdjacencyMatrix.GetLastIndexColumn();
    vector <int> CheckedArray;
    int ActiveNode;
    int i1 = 0;
    int j1 = 0;
    Length.clear();
    ShortestWay.clear();

    for (int i = AdjacencyMatrix.GetFirstIndexColumn(); i<= size; i++){
        if (AdjacencyMatrix.IssetColumn(i)){
            Length.insert(make_pair(i,0));
            ShortestWay.insert(make_pair(i,0));
        }
    }
    int minLength = 0;
    int minNode = 0;
    CheckedArray.push_back(From);
    ActiveNode = From;
    int ActiveLength = 0;
    for (int i = AdjacencyMatrix.GetFirstIndexRow(); i < AdjacencyMatrix.GetLastIndexRow(); i++){
        if (AdjacencyMatrix.IssetColumn(i))
            for (int j = AdjacencyMatrix.GetFirstIndexColumn(); j <= size; j++){
                if (((!(find(CheckedArray.begin(),CheckedArray.end(),j)!= CheckedArray.end()))&&(((ActiveLength+(AdjacencyMatrix(ActiveNode,j)))<Length[j])||(Length[j]==0)))&&(AdjacencyMatrix(ActiveNode,j)!=0)){
                    Length[j]=ActiveLength+AdjacencyMatrix(ActiveNode,j);
                    ShortestWay[j] = ActiveNode;
                }
            }
        minLength = 0;
        for (map<int,int>::iterator len = Length.begin(); len !=Length.end();len++){
            if (((minLength == 0)||(len->second < minLength))&&(len->second!=0)&&(!(find(CheckedArray.begin(),CheckedArray.end(),len->first)!= CheckedArray.end()))){
                minLength = len->second;
                minNode = len->first;
            }
        }
        ActiveNode = minNode;
        CheckedArray.push_back(ActiveNode);
        ActiveLength = minLength;
    }
}

bool Graph::IsEdgeBiDirectional(int Edge, int FirstNode, int SecondNode)
{
    int ControlSum = 1;
    ControlSum *= IncidenceMatrix(Edge, FirstNode);
    ControlSum *= IncidenceMatrix(Edge, SecondNode);
    if (ControlSum >0){
        return true;
    }else{
        return false;
    }
}

int Graph::GetIndexFromHeader(int Header)
{
    for (int i=0;i<NodeHeaders.count();i++){
        if (NodeHeaders[i].toInt()==Header)
            return i;
    }
    return -1;
}

int Graph::GetShortestWayTo(int Node)
{
    return Length[Node];
}

bool Graph::CheckShortestWayToValue(int Node)
{
    if (ShortestWay[Node]!=0)
        return true;
    return false;
}

int Graph::GetCountColumnIncMat()
{
    return IncidenceMatrix.GetCountOfColumns();
}

int Graph::GetCountColumnAdjMat()
{
    return AdjacencyMatrix.GetCountOfColumns();
}

int Graph::GetCountRowIncMat()
{
    return IncidenceMatrix.GetCountOfRows();
}

QStringList Graph::GetDataFromIncMat()
{
    QStringList data;
    int RowCount = -1;
    for (int i = IncidenceMatrix.GetFirstIndexRow(); i!= IncidenceMatrix.GetLastIndexRow()+1; i++){
        if (IncidenceMatrix.IssetRow(i)){
            RowCount++;
            for (int j = IncidenceMatrix.GetFirstIndexColumn(); j!= IncidenceMatrix.GetLastIndexColumn()+1; j++){
                if (IncidenceMatrix.IssetColumn(j)){
                    if(IncidenceMatrix(i,j)!=0){
                        data.push_back(QString::number(RowCount));
                        data.push_back(QString::number(GetIndexFromHeader(j)));
                        data.push_back(QString::number(IncidenceMatrix(i,j)));
                    }
                }
            }
        }
    }
    return data;
}

QStringList Graph::GetDataFromAdjMat()
{
    QStringList data;
    int RowCount = -1;
    for (int i = AdjacencyMatrix.GetFirstIndexRow(); i!= AdjacencyMatrix.GetLastIndexRow()+1; i++){
        if (AdjacencyMatrix.IssetRow(i)){
            RowCount++;
            for (int j = AdjacencyMatrix.GetFirstIndexColumn(); j!= AdjacencyMatrix.GetLastIndexColumn()+1; j++){
                if (AdjacencyMatrix.IssetColumn(j)){
                    if(AdjacencyMatrix(i,j)!=0){
                        data.push_back(QString::number(RowCount));
                        data.push_back(QString::number(GetIndexFromHeader(j)));
                        data.push_back(QString::number(AdjacencyMatrix(i,j)));
                    }
                }
            }
        }
    }
    return data;
}

void Graph::DFC(int Node, map <int,bool> Visited, map <int,int> Colors, string way)
{

    Visited[Node] = true;

    //    for (int i = AdjacencyMatrix.GetFirstIndexColumn(); i<=AdjacencyMatrix.GetLastIndexColumn();i++){
    //        if ((AdjacencyMatrix.IssetColumn(i))and(i!=Node)and(AdjacencyMatrix(Node,i)!=0)and(i!=start)and(predposledniy < Node))
    //            Visited[i]=false;
    //    }

    for (int i = AdjacencyMatrix.GetFirstIndexColumn(); i<= AdjacencyMatrix.GetLastIndexColumn(); i++){
        if ((AdjacencyMatrix.IssetColumn(i))and(AdjacencyMatrix(Node,i)!=0)and(Colors[i]==1)and(predposledniy!=i) ){
            //cout << "Cyrcle"<< endl;
            //if (!CyrcleStack.find(way+'\n'));
            CountOfCyrcle++;
            CyrcleStack += way+"->"+to_string(i)+'\n';
        }
        if ((AdjacencyMatrix.IssetColumn(i))and(AdjacencyMatrix(Node,i)!=0)and(Visited[i]==false)and(Colors[i]!=2)and(predposledniy!=i) ){
            predposledniy = Node;
            DFC(i,Visited,Colors,way+"->"+to_string(i));
            Colors[i]=2;
        }
    }

}


int Graph::GetCountOfCycle()
{
    map <int,int> Colors;
    map <int, bool> Visited;
    string way;
    //0- white
    //1- grey
    //2- black
    //    start = 1;
    //    predposledniy = 1;
    CyrcleStack = "";
    CountOfCyrcle = 0;
    for (int i = AdjacencyMatrix.GetFirstIndexColumn(); i<= AdjacencyMatrix.GetLastIndexColumn(); i++){
        AdjacencyMatrix.IssetColumn(i);{
            Colors.insert(make_pair(i,0));
            Visited.insert(make_pair(i,false));
        }
    }

    for (int i = AdjacencyMatrix.GetFirstIndexColumn(); i<= AdjacencyMatrix.GetLastIndexColumn(); i++){
        AdjacencyMatrix.IssetColumn(i);{
            start = i;
            predposledniy = i;
            way = to_string(i);
            Colors[i] = 1;
            DFC(i,Visited,Colors,way);
            Colors[i] = 2;
        }
    }


    //cout << CyrcleStack << endl;
    return CountOfCyrcle;
}

QStringList Graph::GetCurrentNods()
{
    QStringList Nods;

    for (int i = AdjacencyMatrix.GetFirstIndexColumn(); i <= AdjacencyMatrix.GetLastIndexRow(); i++){
        if (AdjacencyMatrix.IssetColumn(i))
            Nods.push_back(QString::number(i));
    }
    return Nods;
}

string Graph::GetDotFile()
{
    return DotFile;
}

QStringList Graph::GetSecondValueInRowFromIncMatrix(int Row, int Column)
{
    int Value = 0;
    Row++;
    Column++;
    QStringList Values;

    if (IncidenceMatrix.GetCountOfColumns() == 0){
        return Values;
    }
    //GetIncidenceMatrix();
    for (int i = IncidenceMatrix.GetFirstIndexColumn(); i <= IncidenceMatrix.GetLastIndexColumn(); i++){
        if (IncidenceMatrix.IssetColumn(i)){
            if (IncidenceMatrix(Row, i)!=0){
                Value = IncidenceMatrix(Row, i);
                Values.push_back(QString::number(i));
                Values.push_back(QString::number(Value));
            }
        }
    }
    return Values;
}

void Graph::ChangeIncidenceMatrixCell(int Row, int Column, int Value)
{
    Column = NodeHeaders[Column-1].toInt();
    IncidenceMatrix.SetCell(Row, Column, Value);
}

void Graph::ConnectNods(int From, int To, int Length, int EdgeIndex)
{
    EdgeIndex++;
    AddedNods = AddedNods + to_string(From) + "with" + to_string(To)+"-"+to_string(EdgeIndex)+"-";
    AdjacencyMatrix.AddDirectionalEdge(From, To, Length);

}

void Graph::DisconnectNods(int From, int To, int EdgeIndex)
{
    AdjacencyMatrix.AddBidirectionalEdge(From, To, 0);
    EdgeIndex++;
    string Nods =to_string(From) + "with" + to_string(To)+"-"+to_string(EdgeIndex)+"-";

    if (AddedNods.find(Nods)!= std::string::npos){
        AddedNods.erase(AddedNods.find(Nods),Nods.size());
    }
    Nods =to_string(To) + "with" + to_string(From)+"-"+to_string(EdgeIndex)+"-";
    if (AddedNods.find(Nods)!= std::string::npos){
        AddedNods.erase(AddedNods.find(Nods),Nods.size());
    }
}
