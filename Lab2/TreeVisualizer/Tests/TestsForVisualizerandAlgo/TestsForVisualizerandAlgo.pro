QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH+="../../"
INCLUDEPATH+="../../Trees"
INCLUDEPATH += "googletest"
INCLUDEPATH += "googletest/include"
INCLUDEPATH += "googlemock"
INCLUDEPATH += "googlemock/include"

CONFIG+=console c++14

SOURCES += \
    main.cpp \
    ../../creator.cpp \
    ../../imagewriter.cpp \
    ../../mainwindow.cpp \
    ../../Trees/binarytree.cpp \
    ../../Trees/bplustree.cpp \
    ../../Trees/obst.cpp \
    ../../Trees/rbtree.cpp \
    ../../Trees/splaytree.cpp \
    ../../Trees/tree.cpp \
    googlemock/src/gmock-all.cc \
    googletest/src/gtest-all.cc

FORMS += \
    ../../mainwindow.ui

HEADERS += \
    ../../creator.h \
    ../../imagewriter.h \
    ../../mainwindow.h \
    ../../Trees/binarytree.h \
    ../../Trees/bplustree.h \
    ../../Trees/obst.h \
    ../../Trees/rbtree.h \
    ../../Trees/splaytree.h \
    ../../Trees/tree.h
