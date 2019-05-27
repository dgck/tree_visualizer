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
    googletest/src/gtest-all.cc \
    ../../QGVGraphRelated/qgvabstracttreescenefactory.cpp \
    ../../QGVGraphRelated/qgvbinarytreescenefactory.cpp \
    ../../QGVGraphRelated/qgvbtreescenefactory.cpp \
    ../../QGVGraphRelated/qgvformatbuilder.cpp \
    ../../QGVGraphRelated/qgvredblacktreescenefactory.cpp \
    ../../QGVCore/QGVEdge.cpp \
    ../../QGVCore/QGVNode.cpp \
    ../../QGVCore/QGVScene.cpp \
    ../../QGVCore/QGVSubGraph.cpp \
    ../../QGVCore/private/QGVCore.cpp \
    ../../QGVCore/private/QGVEdgePrivate.cpp \
    ../../QGVCore/private/QGVGraphPrivate.cpp \
    ../../QGVCore/private/QGVGvcPrivate.cpp \
    ../../QGVCore/private/QGVNodePrivate.cpp \
    ../../QGVCore/private/qgvrecordprivate.cpp

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
    ../../Trees/tree.h \
    ../../QGVGraphRelated/commons.h \
    ../../QGVGraphRelated/qgvabstracttreescenefactory.h \
    ../../QGVGraphRelated/qgvbinarytreescenefactory.h \
    ../../QGVGraphRelated/qgvbtreescenefactory.h \
    ../../QGVGraphRelated/qgvformatbuilder.h \
    ../../QGVGraphRelated/qgvredblacktreescenefactory.h \
    ../../QGVCore/qgv.h \
    ../../QGVCore/QGVEdge.h \
    ../../QGVCore/QGVNode.h \
    ../../QGVCore/QGVScene.h \
    ../../QGVCore/QGVSubGraph.h \
    ../../QGVCore/private/QGVCore.h \
    ../../QGVCore/private/QGVEdgePrivate.h \
    ../../QGVCore/private/QGVGraphPrivate.h \
    ../../QGVCore/private/QGVGvcPrivate.h \
    ../../QGVCore/private/QGVNodePrivate.h \
    ../../QGVCore/private/qgvrecordprivate.h \
    ../../graphviz/include/graphviz/cgraph.h \
    ../../graphviz/include/graphviz/gvc.h

DISTFILES += \
    ../../QGVCore/GraphViz.pri

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../lib/release/ -lQGVCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../lib/debug/ -lQGVCore
else:unix: LIBS += -L$$PWD/../../lib/ -lQGVCore

INCLUDEPATH += $$PWD/../../
DEPENDPATH += $$PWD/../../
