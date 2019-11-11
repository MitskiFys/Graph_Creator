#ifndef IMAGECREATOR_H
#define IMAGECREATOR_H

#include <QObject>
#include "graphviz/gvc.h"
#include <string>
#include <fstream>
#include<iostream>
using namespace std;
class ImageCreator : public QObject
{
    Q_OBJECT
private:
    const std::string PATH = "graph.svg";
    ifstream PrevFile;
    ifstream CurrentFile;
    bool CompaireFile();
public:
    //ImageCreator();
    bool saveImageGV(std::string);
    bool SendSignal();
    bool CheckFile();
signals:
    void ImageCreated();
};

#endif // IMAGECREATOR_H
