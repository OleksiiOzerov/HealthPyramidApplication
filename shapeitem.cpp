
#include <QtWidgets>
#include <QPen>

#include "shapeitem.h"

ShapeItem::ShapeItem() : myClickNumber(0u)
{
    myPen = QPen(Qt::NoPen);
}

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

QPen ShapeItem::pen() const
{
    return myPen;
}

size_t ShapeItem::clickNumber() const
{
    return myClickNumber;
}

FigureType ShapeItem::type() const
{
    return myType;
}

void ShapeItem::itemClicked()
{
    ++myClickNumber;
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

void ShapeItem::setPen(const QPen &pen)
{
    myPen = pen;
}

void ShapeItem::setType(const FigureType type)
{
    myType = type;
}


