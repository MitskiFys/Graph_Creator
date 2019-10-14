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
        cout << IncidenceMatrix.IssetRow(3);
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

void Graph::DeleteEdge(int Number)
{
    int FirstNode = 0;
    int SecondNode = 0;
    cout << IncidenceMatrix.IssetRow(3);
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

void Graph::GetDotFile()
{

    std::ofstream outfile ("graph.dot");
    int FirtsNode = 0;
    int SecondNode = 0;
    int Direction = 1;
    outfile << "digraph graphname {"<< endl;
    cout << "------------------"<< endl;
    GetAdjacencyMatrix();
    cout << endl;
    GetIncidenceMatrix();
    cout << "------------------"<< endl;
    for (int i = AdjacencyMatrix.GetFirstIndexRow(); i<= AdjacencyMatrix.GetLastIndexRow();i++){
        if (AdjacencyMatrix.IssetRow(i)){
            outfile << i << ';' << endl;
        }
    }

    if (IncidenceMatrix.GetCountOfColumns()!=0){
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
                if (FirtsNode == 0){
                    FirtsNode = SecondNode;
                    Direction*=-1;
                }
                outfile << FirtsNode;
                if (Direction < 0) {
                    outfile << "->"<< SecondNode <<"[label = "<<AdjacencyMatrix(FirtsNode,SecondNode)<<"]"<< endl;
                } else {
                    outfile << "->"<< SecondNode <<"[dir=\"both\",label ="<<AdjacencyMatrix(FirtsNode,SecondNode)<<"]"<< endl;
                }
                FirtsNode =0;
                SecondNode = 0;
                Direction = 1;
            }

        }
    }
    outfile <<"}"<<endl;

    outfile.close();
}

void Graph::GetDotFile(int From = 0, int To = 0)
{
    std::ofstream outfile ("graph.dot");
    int FirtsNode = 0;
    int SecondNode = 0;
    int Direction = 1;
    outfile << "digraph graphname {"<< endl;
    map <int, int> Way;

    if (CheckShortestWayToValue(To))
        while (From != To){
            Way.insert(make_pair(To,ShortestWay[To]));
            To = ShortestWay[To];
        }
    for (int i = AdjacencyMatrix.GetFirstIndexRow(); i<= AdjacencyMatrix.GetLastIndexRow();i++){
        if (AdjacencyMatrix.IssetRow(i)){
            outfile << i << ';' << endl;
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
            if (FirtsNode == 0){
                FirtsNode = SecondNode;
                Direction*=-1;
            }
            //cout << Way[SecondNode] << endl;
            if (!(((Way.find(SecondNode)!=Way.end())&&(Way[SecondNode]==FirtsNode)))){
                outfile << FirtsNode;
                if (Direction < 0) {
                    outfile << "->"<< SecondNode <<"[label = "<<AdjacencyMatrix(FirtsNode,SecondNode)<<"]"<< endl;
                } else {
                    outfile << "->"<< SecondNode <<"[dir=\"both\",label ="<<AdjacencyMatrix(FirtsNode,SecondNode)<<"]"<< endl;
                }
                FirtsNode =0;
                SecondNode = 0;
                Direction = 1;
            } else {
                outfile << FirtsNode;
                if (Direction < 0) {
                    outfile << "->"<< SecondNode <<" [color = Red"<<",label = "<<AdjacencyMatrix(FirtsNode,SecondNode)<<"]"<< endl;
                } else {
                    outfile << "->"<< SecondNode <<"[dir=\"both\", color = Red, label ="<<AdjacencyMatrix(FirtsNode,SecondNode)<<"]"<< endl;
                }
                FirtsNode =0;
                SecondNode = 0;
                Direction = 1;
            }

        }

    }

    outfile <<"}"<<endl;

    outfile.close();
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
    Headers << Number;
}

void Graph::DeleteHeader(int Node)
{
    QString Number =QString::number(Node);
    Headers.removeOne(Number);
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
    cout << endl;
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
    for (int i=0;i<Headers.count();i++){
        if (Headers[i].toInt()==Header)
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

void Graph::DFC(int Node, map <int,bool> Visited, map <int,int> Colors, string way)
{

    Visited[Node] = true;

    //    for (int i = AdjacencyMatrix.GetFirstIndexColumn(); i<=AdjacencyMatrix.GetLastIndexColumn();i++){
    //        if ((AdjacencyMatrix.IssetColumn(i))and(i!=Node)and(AdjacencyMatrix(Node,i)!=0)and(i!=start)and(predposledniy < Node))
    //            Visited[i]=false;
    //    }

    for (int i = AdjacencyMatrix.GetFirstIndexColumn(); i<= AdjacencyMatrix.GetLastIndexColumn(); i++){
        if ((AdjacencyMatrix.IssetColumn(i))and(AdjacencyMatrix(Node,i)!=0)and(Colors[i]==1)and(predposledniy!=i) ){
            cout << "Cyrcle"<< endl;
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


    cout << CyrcleStack << endl;
    return CountOfCyrcle;
}








