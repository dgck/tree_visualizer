#-------------------------------------------------
#
# Project created by QtCreator 2019-04-18T20:17:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TreeVisualizer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11


SRCDIRRR = /home/artyom/qtprojects/qgv/lib
LIBS += -L$$SRCDIRRR/../lib -lQGVCore
INCLUDEPATH += /home/artyom/qtprojects/qgv/QGVCore
DEPENDPATH += /home/artyom/qtprojects/qgv/QGVCore

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    imagewriter.cpp \
    creator.cpp \
    Trees/binarytree.cpp \
    Trees/bplustree.cpp \
    Trees/obst.cpp \
    Trees/rbtree.cpp \
    Trees/splaytree.cpp \
    Trees/tree.cpp \
	qcgview.cpp \
    QGVGraphRelated/qgvcontextfactory.cpp \
    QGVGraphRelated/qgvabstracttreescenefactory.cpp \
    QGVGraphRelated/qgvredblacktreescenefactory.cpp


HEADERS += \
        mainwindow.h \
    imagewriter.h \
    creator.h \
    Trees/binarytree.h \
    Trees/bplustree.h \
    Trees/obst.h \
    Trees/rbtree.h \
    Trees/splaytree.h \
    Trees/tree.h \
        qcgview.h \
    QGVGraphRelated/qgvcontextfactory.h \
    QGVGraphRelated/qgvabstracttreescenefactory.h \
    QGVGraphRelated/qgvredblacktreescenefactory.h \
    QGVGraphRelated/commons.h




FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
