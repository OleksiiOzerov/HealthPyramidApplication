
#include <QtWidgets>

#include "shapeitem.h"

QPainterPath ShapeItem::path() const
{
    return myPath;
}

QPoint ShapeItem::position() const
{
    return myPosition;
}

QColor ShapeItem::color() const
{
    return myColor;
}

QString ShapeItem::toolTip() const
{
    return myToolTip;
}

QBrush ShapeItem::brush() const
{
    return myBrush;
}

void ShapeItem::setPath(const QPainterPath &path)
{
    myPath = path;
}

void ShapeItem::setToolTip(const QString &toolTip)
{
    myToolTip = toolTip;
}

void ShapeItem::setPosition(const QPoint &position)
{
    myPosition = position;
}

void ShapeItem::setColor(const QColor &color)
{
    myColor = color;
}


void ShapeItem::setBrush(const QBrush &brush)
{
    myBrush = brush;
}
