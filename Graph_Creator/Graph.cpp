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
    AdjacencyMatrix.DeleteNode(Number);
    vector <int> NumberToDelete;
    for (int i = IncidenceMatrix.GetFirstIndexRow(); i <=IncidenceMatrix.GetLastIndexRow()+1;i++){
        if ((IncidenceMatrix.IssetRow(i))&&(IncidenceMatrix(i,Number)!=0)) {
            NumberToDelete.push_back(i);//5,6,10,14,
        }
    }
    for (vector <int>::iterator iter = NumberToDelete.begin(); iter!=NumberToDelete.end();iter++){
        IncidenceMatrix.DeleteRow(*iter);
    }
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
                IncidenceMatrix.AddColumn();
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

    for (int i = 1; i <= IncidenceMatrix.GetCountOfColumns();i++) {
        if (IncidenceMatrix(Number, i) != 0) {
            FirstNode = SecondNode;
            SecondNode = i;
        }
    }
    if (FirstNode==0)
        FirstNode = SecondNode;
    string Nods =to_string(FirstNode) + "with" + to_string(SecondNode)+"-"+to_string(Number)+"-";

    IncidenceMatrix.DeleteRow(Number);
    AdjacencyMatrix.AddBidirectionalEdge(FirstNode, SecondNode, 0);
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

void Graph::GetDotFile(int From, int To)
{
    RunAlgoDijkstra(From);
    From--;
    To--;
    std::ofstream outfile ("graph.dot");
    int FirtsNode = 0;
    int SecondNode = 0;
    int Direction = 1;
    outfile << "digraph graphname {"<< endl;
    map <int, int> Way;

    while (From != To){
        Way.insert(make_pair((To+1),(ShortestWay[To]+1)));
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
            string find;
            find = to_string(FirtsNode) + " " + to_string(SecondNode);
            if (!((FirtsNode<=Way.size())&&((Way[(SecondNode)]==(FirtsNode))||((Direction > 0)&&((Way[(FirtsNode)]==(SecondNode))))))){
                outfile << FirtsNode;
                if (Direction < 0) {
                    outfile << "->"<< SecondNode << endl;
                } else {
                    outfile << "->"<< SecondNode <<"[dir=\"both\"]"<< endl;
                }
                FirtsNode =0;
                SecondNode = 0;
                Direction = 1;
            } else {
                outfile << FirtsNode;
                if (Direction < 0) {
                    outfile << "->"<< SecondNode <<" [color = Red]"<< endl;
                } else {
                    outfile << "->"<< SecondNode <<"[dir=\"both\", color = Red]"<< endl;
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
    int size = AdjacencyMatrix.GetCountOfColumns();
    int* Headers = new int[size];
    int** ptrarray = new int* [size];
    vector <int> CheckedArray;
    int ActiveNode;
    int i1 = 0;
    int j1 = 0;
    From--;
    for (int count = 0; count < size; count++)
        ptrarray[count] = new int [size];
    for (int i = AdjacencyMatrix.GetFirstIndexRow(); i<= AdjacencyMatrix.GetLastIndexRow(); i++){
        if (AdjacencyMatrix.IssetRow(i))
        {
            Headers[i1]=i;
            for (int j = AdjacencyMatrix.GetFirstIndexColumn(); j <= AdjacencyMatrix.GetLastIndexColumn(); j++){
                ptrarray[i1][j1]=AdjacencyMatrix(i,j);
                j1++;
            }
            j1=0;
            i1++;
        }
    }
    for (int i = 0; i < size; i++){
        Length.push_back(0);
        ShortestWay.push_back(From);
    }
    int minLength = 0;
    int minNode = 0;
    CheckedArray.push_back(From);
    ActiveNode = From;
    int ActiveLength = 0;
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            //cout << (find(CheckedArray.begin(),CheckedArray.end(),j)!= CheckedArray.end()) << endl;
            //cout << ptrarray[ActiveNode][j] << endl;
            if (((!(find(CheckedArray.begin(),CheckedArray.end(),j)!= CheckedArray.end()))&&(((ActiveLength+ptrarray[ActiveNode][j])<Length[j])||(Length[j]==0)))&&(ptrarray[ActiveNode][j]!=0)){
                Length[j]=ActiveLength+ptrarray[ActiveNode][j];
                ShortestWay[j] = ActiveNode;

            }
        }
        int key = 0;
        minLength = 0;
        for (auto len : Length){
            if (((minLength == 0)||(len < minLength))&&(len!=0)&&(!(find(CheckedArray.begin(),CheckedArray.end(),key)!= CheckedArray.end()))){
                minLength = len;
                minNode = key;
                key++;
            } else {
                key++;
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
    for (int i=0;i<Headers.count()-1;i++){
        if (Headers[i]==Header)
            return i;
    }
    return -1;
}
