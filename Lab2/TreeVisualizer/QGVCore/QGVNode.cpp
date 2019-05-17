/***************************************************************
QGVCore
Copyright (c) 2014, Bergont Nicolas, All rights reserved.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 3.0 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library.
***************************************************************/
#include <QGVNode.h>
#include <QGVCore.h>
#include <QGVScene.h>
#include <QGVGraphPrivate.h>
#include <QGVNodePrivate.h>
#include <QDebug>
#include <QPainter>
#include <QString>
#include <QList>
#include <QString>
#include <QDataStream>
#include "QGVGvcPrivate.h"

QGVNode::QGVNode(QGVNodePrivate *node, QGVScene *scene): _scene(scene), _node(node)
{
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    record_mode = false;
}

QGVNode::~QGVNode()
{
    _scene->removeItem(this);
    delete _node;
}

QString QGVNode::label() const
{
    return getAttribute("label");
}

void QGVNode::setLabel(const QString &label)
{
    setAttribute("label", label);
}

QRectF QGVNode::boundingRect() const
{
    return _path.boundingRect();
}

#include <iostream>
using namespace std;

void QGVNode::paint(QPainter * painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->save();

    painter->setPen(_pen);

    if(isSelected())
    {
        QBrush tbrush(_brush);
        tbrush.setColor(tbrush.color().darker(120));
        painter->setBrush(tbrush);
    }
    else
        painter->setBrush(_brush);

    painter->drawPath(_path);

    painter->setPen(QGVCore::toColor(getAttribute("labelfontcolor")));

    if (!record_mode)
    {

        const QRectF rect = boundingRect().adjusted(2,2,-2,-2); //Margin
        if(_icon.isNull())
        {
            painter->drawText(rect, Qt::AlignCenter , QGVNode::label());
        }
        else
        {
            painter->drawText(rect.adjusted(0,0,0, -rect.height()*2/3), Qt::AlignCenter , QGVNode::label());

            const QRectF img_rect = rect.adjusted(0, rect.height()/3,0, 0);
            QImage img = _icon.scaled(img_rect.size().toSize(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            painter->drawImage(img_rect.topLeft() + QPointF((img_rect.width() - img.rect().width())/2, 0), img);
        }
    } else
    {
        qDebug() << "fuck";
        // get the names of the nodes
        QString label_text = label(),
                label_text_clean = QString();

        for (int i = 0; i < label_text.size(); i++)
        {
            if (label_text[i] == '<')
                while (label_text[i] != '>')
                    i++;
            else
                qDebug() << "ok";
            label_text_clean += label_text[i];
            qDebug() << "cur labrl_text_clean";
            qDebug() << label_text_clean;
        }

        qDebug() << "---clean text: ";
        qDebug() << label_text_clean;

        QStringList label_list = label_text.split('|');

        qDebug() << "label list";
        for (int i = 0; i < label_list.size(); i++)
        {
            qDebug() << label_list[i];
        }

        //get the position data in strings of format "%f,%f,%f,%f"

        QStringList position_data_raw = getAttribute("rects").split(' ');
        QList <QList <qreal>> position_data;

        for (int i = 0; i < position_data_raw.size(); i++)
        {
            qDebug() << "--press";
            QStringList temp_list = position_data_raw[i].split(',');
            qDebug() << "--press";
            QList <qreal> temp_list_reals;
            qDebug() << "--press";
            for (int i = 0; i < 4; i++)
            {
                temp_list_reals.append(temp_list.at(i).toDouble());
            }
            position_data.append(temp_list_reals);
            //position_data.append(str.split(','));
        }

        QDataStream stream;
        char* buf;
        stream >> buf;

        qDebug() << "---position data";
        for (int i = 0; i < position_data.size(); i++)
        {
            qDebug() << position_data[i];
        }

        for (int i = 0; i < label_list.size(); i++)
        {
            qreal width = ND_width(_node->node())*DotDefaultDPI;
            qreal height = ND_height(_node->node())*DotDefaultDPI / position_data.size();

            polygon_t poly;
            poly.peripheries = 1;
            poly.sides = 4;
            poly.vertices[0] = pointf{(position_data[i][0]), (position_data[i][1])};
            poly.vertices[1] = pointf{(position_data[i][0] + width), (position_data[i][1])};
            poly.vertices[2] = pointf{(position_data[i][0]), (position_data[i][1] + height)};
            poly.vertices[3] = pointf{(position_data[i][0] + width), (position_data[i][1] + height)};

            // нужен свой polygon_t, высота та же, ширина /= list.size(), shape = "record"
            _path = QGVCore::toPath("record", &poly, width, height);

            /*
                вызовется создание polygon_t, что за width, hight? - это высота и ширина узла
            */

            /*
                format : const char *type, const polygon_t *poly, qreal width, qreal height
            */

            /*
                painter->drawPath(_path);
                painter->setPen(QGVCore::toColor(getAttribute("labelfontcolor")));
                const QRectF rect = boundingRect().adjusted(2,2,-2,-2); //Margin
                painter->drawText(rect, Qt::AlignCenter , QGVNode::label());
            */


            painter -> drawPath(_path);
            painter -> setPen(QGVCore::toColor(getAttribute("labelfontcolor")));

            // заходим только один раз в эту функцию
            const QRectF rect = boundingRect().adjusted(2, 2, -2, -2);
            painter -> drawText(rect, Qt::AlignCenter, QString(label_text_clean[i]));
        }
    }
    painter->restore();
}

void QGVNode::setAttribute(const QString &name, const QString &value)
{
    if (name == "shape" && value == "record")
    {
        record_mode = true;
    }

    char empty[] = "";
    agsafeset(_node->node(), name.toLocal8Bit().data(), value.toLocal8Bit().data(), empty);

    gvLayout (_scene -> _context -> _context, _node -> graph(), "dot");
    gvRender (_scene -> _context ->_context, _node ->graph(), "dot", NULL);
    gvFreeLayout(_scene -> _context -> _context, _node -> graph());
}

QString QGVNode::getAttribute(const QString &name) const
{
    char* value = agget(_node->node(), name.toLocal8Bit().data());
    if(value)
        return value;
    return QString();
}

void QGVNode::setIcon(const QImage &icon)
{
    _icon = icon;
}

void QGVNode::updateLayout()
{
    prepareGeometryChange();
    qreal width = ND_width(_node->node())*DotDefaultDPI;
    qreal height = ND_height(_node->node())*DotDefaultDPI;

    //Node Position (center)
    qreal gheight = QGVCore::graphHeight(_scene->_graph->graph());
    setPos(QGVCore::centerToOrigin(QGVCore::toPoint(ND_coord(_node->node()), gheight), width, height));

    //Node on top
    setZValue(1);

    //Node path
    _path = QGVCore::toPath(ND_shape(_node->node())->name, (polygon_t*)ND_shape_info(_node->node()), width, height);
    _pen.setWidth(1);

    _brush.setStyle(QGVCore::toBrushStyle(getAttribute("style")));
    _brush.setColor(QGVCore::toColor(getAttribute("fillcolor")));
    _pen.setColor(QGVCore::toColor(getAttribute("color")));

    setToolTip(getAttribute("tooltip"));
}
