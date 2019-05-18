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
#include <vector>
using std::vector;
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
        const QRectF rect = boundingRect().adjusted(2,2,-2,-2);
        painter->drawText(rect.adjusted(0,0,0, -rect.height()*2/3), Qt::AlignCenter , QGVNode::label());

        QString label_text = label(),
                label_text_clean = QString();

        for (int i = 0; i < label_text.size(); i++)
        {
            if (label_text[i] == '<')
                while (label_text[i] != '>')
                    i++;
            label_text_clean += label_text[i];
        }

        QStringList label_list = label_text.split('|');
        vector <const QRectF*> vec;

        for (int i = 0; i < label_list.size(); i++)
        {
            QRectF rect_t_n = _path_records[i].boundingRect();
            QRectF *rect_t_p = &rect_t_n;
            vec.push_back(const_cast <QRectF*> (rect_t_p));
            painter -> drawText(vec.back()->adjusted(0,0,0, -vec.back()->height()*2/3), Qt::AlignCenter , label_list[i]);
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
    // THIS WILL NOT WORK BECAUSE THE SHAPE FOR "RECROD"IS NOT POLYGON_T, WE NEED TO PARSE THIS RECURSIVELY (FIELD_T)

    if (!record_mode)
        _path = QGVCore::toPath(ND_shape(_node->node())->name, (polygon_t*)ND_shape_info(_node->node()), width, height);
    else
    {
        field_t* info_general = (field_t*)ND_shape_info(_node -> node());
        width = info_general->size.x;
        height = info_general -> size.y;
        polygon_t info_poly;
        info_poly.option = 0;
        info_poly.distortion = 0;
        info_poly.orientation = 0;
        info_poly.peripheries = 1;
        info_poly.sides = 4;
        info_poly.skew = 0;
        info_poly.regular = 0;
        info_poly.vertices = new pointf[4];
        info_poly.vertices[0] = pointf{info_general->b.LL.x, info_general->b.LL.y};
        info_poly.vertices[1] = pointf{info_general->b.LL.x + width, info_general->b.LL.y};
        info_poly.vertices[2] = pointf{info_general->b.LL.x, info_general->b.LL.y + height};
        info_poly.vertices[3] = pointf{info_general->b.UR.x, info_general->b.UR.y};

        _path = QGVCore::toPath("rectangle", &info_poly, width, height);

        int sz = info_general->n_flds;
        for (int i = 0; i < sz; i++)
        {
            field_t* info_special = info_general->fld[i];
            width = info_special->size.x;
            height = info_special -> size.y;
            info_poly.option = 0;
            info_poly.distortion = 0;
            info_poly.orientation = 0;
            info_poly.peripheries = 1;
            info_poly.sides = 4;
            info_poly.skew = 0;
            info_poly.regular = 0;
            info_poly.vertices = new pointf[4];
            info_poly.vertices[0] = pointf{info_special->b.LL.x, info_special->b.LL.y};
            info_poly.vertices[1] = pointf{info_special->b.LL.x + width, info_special->b.LL.y};
            info_poly.vertices[2] = pointf{info_special->b.LL.x, info_special->b.LL.y + height};
            info_poly.vertices[3] = pointf{info_special->b.UR.x, info_special->b.UR.y};
            const polygon_t poly_const = info_poly;
            _path_records[i] = QGVCore::toPath("rectangle", &poly_const, width, height);
        }
    }

    _pen.setWidth(1);

    _brush.setStyle(QGVCore::toBrushStyle(getAttribute("style")));
    _brush.setColor(QGVCore::toColor(getAttribute("fillcolor")));
    _pen.setColor(QGVCore::toColor(getAttribute("color")));

    setToolTip(getAttribute("tooltip"));
}
