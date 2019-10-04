#include "mainwindow.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <graphviz/gvc.h>
#include <Graph.h>

using namespace std;




int main(int argc, char *argv[])
{
//    Graph grp;
//    int status = 0;
//    int key = 0;
//    while (status == 0){
//        cout << "What do you want?"<< endl;
//        cout << "1 - Add Node"<< endl;
//        cout << "2 - Add Directional edge"<< endl;
//        cout << "3 - Add Bidirectional edge"<< endl;
//        cout << "4 - Delete Node"<< endl;
//        cout << "5 - Draw Graph" << endl;
//        cout << "6"<<endl;
//        cin >> key;
//        system("clear");
//        switch (key)
//        {
//        case 1:{
//            grp.AddNode();
//            grp.GetAdjacencyMatrix();
//            grp.GetIncidenceMatrix();
//            break;
//        }
//        case 2:{
//            cout << "First Node - ";
//            int firstnode = 0;
//            int secondnode = 0;
//            int length = 0;
//            cin >>  firstnode;
//            cout << endl << "Second Node - ";
//            cin >> secondnode;
//            cout << endl<<"Length - ";
//            cin >> length;
//            cout << endl;
//            grp.AddDirectionalEdge(firstnode,secondnode,length);
//            grp.GetAdjacencyMatrix();
//            grp.GetIncidenceMatrix();
//            break;
//        }
//        case 3:{
//            int firstnode = 0;
//            int secondnode = 0;
//            int length = 0;
//            cout << "First Node - ";
//            cin >>  firstnode;
//            cout << endl << "Second Node - ";
//            cin >> secondnode;
//            cout << endl<<"Length - ";
//            cin >> length;
//            cout << endl;
//            grp.AddBidirectionalEdge(firstnode,secondnode,length);
//            grp.GetAdjacencyMatrix();
//            grp.GetIncidenceMatrix();
//            break;
//        }
//        case 4:{
//            cout << "Which node you want to delete? ";
//            int node = 0;
//            cin >> node;
//            cout << endl;
//            grp.DeleteNode(node);
//            grp.GetAdjacencyMatrix();
//            grp.GetIncidenceMatrix();
//            break;
//        }
//        case 5:{
//            status++;
//            grp.GetDotFile();
//            saveImageGV("graph");
//            break;
//        }
//        case 6:{
//            int node;
//            cin >> node;
//            grp.RunAlgoDijkstra(node);
//            cout << endl;
//            break;
//        }
//        case 7:{
//            status++;
//            int From,To;
//            cin >> From;
//            cin >> To;
//            grp.GetDotFile(From,To);
//            saveImageGV("graph");
//            break;
//        }
//        }

//    }
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}



