
#include "PyramidItem.hpp"

#include <QtWidgets>
#include <QPen>

PyramidItem::PyramidItem(size_t GreenColorClickNumber) :
    m_ClickNumber(0u),
    m_GreenColorClickNumber(GreenColorClickNumber),
    m_Position(0, 0),
    m_Color(QColor(255, 0, 0)),
    m_Pen(QPen(Qt::NoPen)),
    m_Brush(m_Color)
{
}

QPainterPath PyramidItem::path() const
{
    return m_Path;
}

QPoint PyramidItem::position() const
{
    return m_Position;
}

QColor PyramidItem::color() const
{
    return m_Color;
}

QString PyramidItem::toolTip() const
{
    return m_ToolTip;
}

QBrush PyramidItem::brush() const
{
    return m_Brush;
}

QPen PyramidItem::pen() const
{
    return m_Pen;
}

size_t PyramidItem::clickNumber() const
{
    return m_ClickNumber;
}

void PyramidItem::itemClicked()
{
    if (m_GreenColorClickNumber * 2 != m_ClickNumber)
    {
        ++m_ClickNumber;
    }

    if (m_GreenColorClickNumber == m_ClickNumber)
    {
       m_Pen = QPen(QColor(0, 255, 0));
       m_Color = QColor(0, 255, 0);
    }
    else if (m_GreenColorClickNumber / 2 == m_ClickNumber)
    {
       m_Pen = QPen(QColor(255, 255, 0));
       m_Color = QColor(255, 255, 0);
    }
    else if (m_ClickNumber == 1)
    {
       m_Pen = QPen(QColor(255, 0, 0));
       m_Color = QColor(255, 0, 0);
    }
}

void PyramidItem::setPath(const QPainterPath &path)
{
    m_Path = path;
}

void PyramidItem::setToolTip(const QString &toolTip)
{
    m_ToolTip = toolTip;
}

void PyramidItem::setPosition(const QPoint &position)
{
    m_Position = position;
}

void PyramidItem::setColor(const QColor &color)
{
    m_Color = color;
}

void PyramidItem::setBrush(const QBrush &brush)
{
    m_Brush = brush;
}

void PyramidItem::setPen(const QPen &pen)
{
    m_Pen = pen;
}
