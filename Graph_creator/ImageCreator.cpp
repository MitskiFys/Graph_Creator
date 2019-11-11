#include "ImageCreator.h"

#include <qthread.h>
#include <thread>

bool ImageCreator::saveImageGV(std::string DotFile){
    GVC_t *gvc;
    Agraph_t *g;
    gvc = gvContext();
    char cstr[DotFile.size()+1];
    strcpy(cstr, DotFile.c_str());
    g = agmemread(cstr);
    gvLayout(gvc, g, "dot");
    std::string FileName = PATH;
    gvRender(gvc, g, "svg", fopen((FileName).c_str(), "w"));
    //QThread::msleep(100);
    gvFreeLayout(gvc, g);
    SendSignal();
    return true;
}

bool ImageCreator::SendSignal()
{
    CurrentFile.open(PATH);
    while (CurrentFile){
        CurrentFile.open(PATH);
    }
    emit ImageCreated();
    return true;
}

bool ImageCreator::CheckFile()
{
    std::ifstream file;
    file.open(PATH);
    if(file)
        return true;
    return false;
}

