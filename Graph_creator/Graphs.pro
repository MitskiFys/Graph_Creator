QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
QT       += svg
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Graph.cpp \
    ImageCreator.cpp \
    Matrix.cpp \
    MyEllipse.cpp \
    MyScene.cpp \
    WidgetMatrixData.cpp \
    WidgetVisualGraph.cpp \
    main.cpp \

HEADERS += \
    Graph.h \
    ImageCreator.h \
    Matrix.h \
    MyEllipse.h \
    MyScene.h \
    WidgetMatrixData.h \ \
    WidgetVisualGraph.h


LIBS += -lgvc -lcgraph -lcdt

CONFIG += console
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
