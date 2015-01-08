/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "sortingbox.h"

#include <QtWidgets>
#include <stdlib.h>

SortingBox::SortingBox() : m_FoodPiramidFigureShift(0,100), m_InitialColor(255,0,0),
    m_GreenColorLevelCollection({0, 0, 0, 0, 0, 0, 0}),
    m_PressFigureCountCollection({0, 0, 0, 0, 0, 0, 0})
{
    initializeColorCollection();
    initializePressCountCollection();

    setWindowTitle(tr("Food Pyramid"));
    resize(500, 500);

    setMouseTracking(true);

    setBackgroundRole(QPalette::Base);

    itemInMotion = 0;

    createFirstLevelFigure();

    createSecondLevelLeftFigure();
    createSecondLevelRightFigure();

    createThirdLevelLeftFigure();
    createThirdLevelRightFigure();

    createForthLevelLeftFigure();

    createShapeItem(m_FirstLevelFigure, tr("Fats, Oils, & Sweets"),
                    m_FoodPiramidFigureShift + QPoint(200, 0),
                    m_InitialColor);

    createShapeItem(m_SecondLevelLeftFigure, tr("Milk, Yogurt, & Cheese Group"),
                    m_FoodPiramidFigureShift + QPoint(171, 87),
                    m_InitialColor);

    createShapeItem(m_SecondLevelRightFigure, tr("Meat, Poultry, Fish, Dry Beans, Eggs, & Nuts Group"),
                    m_FoodPiramidFigureShift + QPoint(250, 87),
                    m_InitialColor);

    createShapeItem(m_ThirdLevelLeftFigure, tr("Vegetable Group"),
                    m_FoodPiramidFigureShift + QPoint(142, 137),
                    m_InitialColor);

    createShapeItem(m_ThirdLevelRightFigure, tr("Fruit Group"),
                    m_FoodPiramidFigureShift + QPoint(250, 137),
                    m_InitialColor);

    createShapeItem(m_ForthLevelFigure, tr("Bread, Cereal, Rise, & Pasta Group"),
                    m_FoodPiramidFigureShift + QPoint(113, 187),
                    m_InitialColor);
}

bool SortingBox::event(QEvent *event)
{
    if (event->type() == QEvent::ToolTip) {
        QHelpEvent *helpEvent = static_cast<QHelpEvent *>(event);
        int index = itemAt(helpEvent->pos());
        if (index != -1) {
            QToolTip::showText(helpEvent->globalPos(), shapeItems[index].toolTip());
        } else {
            QToolTip::hideText();
            event->ignore();
        }

        return true;
    }
    return QWidget::event(event);
}

void SortingBox::resizeEvent(QResizeEvent * /* event */)
{
}

void SortingBox::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    foreach (ShapeItem shapeItem, shapeItems)
    {

        painter.translate(shapeItem.position());

        painter.setBrush(shapeItem.color());
        painter.drawPath(shapeItem.path());
        painter.translate(-shapeItem.position());
    }
}



void SortingBox::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        int index = itemAt(event->pos());
        if (index != -1)
        {
           itemInMotion = &shapeItems[index];

           size_t greenColorNumberTypeMax = m_GreenColorLevelCollection[index];
           ++m_PressFigureCountCollection[index];

           if (greenColorNumberTypeMax == m_PressFigureCountCollection[index])
           {
                itemInMotion->setColor(QColor(0, 255, 0));
           }
           else if (greenColorNumberTypeMax / 2 == m_PressFigureCountCollection[index])
           {
                itemInMotion->setColor(QColor(255, 255, 0));
           }

            update();
        }
    }
}

void SortingBox::initializeColorCollection()
{
    m_GreenColorLevelCollection[0] = 1;
    m_GreenColorLevelCollection[1] = 3;
    m_GreenColorLevelCollection[2] = 3;
    m_GreenColorLevelCollection[3] = 5;
    m_GreenColorLevelCollection[4] = 3;
    m_GreenColorLevelCollection[5] = 11;
}

void SortingBox::initializePressCountCollection()
{
    m_PressFigureCountCollection[0] = 0;
    m_PressFigureCountCollection[1] = 0;
    m_PressFigureCountCollection[2] = 0;
    m_PressFigureCountCollection[3] = 0;
    m_PressFigureCountCollection[4] = 0;
    m_PressFigureCountCollection[5] = 0;
}

void SortingBox::createFirstLevelFigure()
{
    m_FirstLevelFigure.moveTo(100 / 2, 0);
    m_FirstLevelFigure.lineTo(0      , 87);
    m_FirstLevelFigure.lineTo(100    , 87);
    m_FirstLevelFigure.lineTo(100 / 2, 0);
}

void SortingBox::createSecondLevelLeftFigure()
{
    m_SecondLevelLeftFigure.moveTo(29, 0);
    m_SecondLevelLeftFigure.lineTo(79, 0);
    m_SecondLevelLeftFigure.lineTo(79, 50);
    m_SecondLevelLeftFigure.lineTo(0 , 50);
    m_SecondLevelLeftFigure.lineTo(29, 0);
}

void SortingBox::createSecondLevelRightFigure()
{
    m_SecondLevelRightFigure.moveTo(0, 0);
    m_SecondLevelRightFigure.lineTo(50, 0);
    m_SecondLevelRightFigure.lineTo(80, 50);
    m_SecondLevelRightFigure.lineTo(0 , 50);
    m_SecondLevelRightFigure.lineTo(0, 0);
}

void SortingBox::createThirdLevelLeftFigure()
{
    m_ThirdLevelLeftFigure.moveTo(29, 0);
    m_ThirdLevelLeftFigure.lineTo(108, 0);
    m_ThirdLevelLeftFigure.lineTo(108, 50);
    m_ThirdLevelLeftFigure.lineTo(0 , 50);
    m_ThirdLevelLeftFigure.lineTo(29, 0);
}

void SortingBox::createThirdLevelRightFigure()
{
    m_ThirdLevelRightFigure.moveTo(0, 0);
    m_ThirdLevelRightFigure.lineTo(79, 0);
    m_ThirdLevelRightFigure.lineTo(108, 50);
    m_ThirdLevelRightFigure.lineTo(0 , 50);
    m_ThirdLevelRightFigure.lineTo(0, 0);
}

void SortingBox::createForthLevelLeftFigure()
{
    m_ForthLevelFigure.moveTo(29, 0);
    m_ForthLevelFigure.lineTo(245, 0);
    m_ForthLevelFigure.lineTo(274, 50);
    m_ForthLevelFigure.lineTo(0 , 50);
    m_ForthLevelFigure.lineTo(29, 0);
}

int SortingBox::itemAt(const QPoint &pos)
{
    for (int i = shapeItems.size() - 1; i >= 0; --i) {
        const ShapeItem &item = shapeItems[i];
        if (item.path().contains(pos - item.position()))
            return i;
    }
    return -1;
}

void SortingBox::moveItemTo(const QPoint &pos)
{
    QPoint offset = pos - previousPosition;
    itemInMotion->setPosition(itemInMotion->position() + offset);

    previousPosition = pos;
    update();
}

int SortingBox::updateButtonGeometry(QToolButton *button, int x, int y)
{
    QSize size = button->sizeHint();
    button->setGeometry(x - size.rwidth(), y - size.rheight(),
                        size.rwidth(), size.rheight());

    return y - size.rheight()
           - style()->pixelMetric(QStyle::PM_DefaultLayoutSpacing);
}

void SortingBox::createShapeItem(const QPainterPath &path,
                                 const QString &toolTip, const QPoint &pos,
                                 const QColor &color)
{
    ShapeItem shapeItem;
    shapeItem.setPath(path);
    shapeItem.setToolTip(toolTip);
    shapeItem.setPosition(pos);
    shapeItem.setColor(color);
    shapeItems.append(shapeItem);
    update();
}

QPoint SortingBox::initialItemPosition(const QPainterPath &path)
{
    int x;
    int y = (height() - (int)path.controlPointRect().height()) / 2;
    if (shapeItems.size() == 0)
        x = ((3 * width()) / 2 - (int)path.controlPointRect().width()) / 2;
    else
        x = (width() / shapeItems.size()
             - (int)path.controlPointRect().width()) / 2;

    return QPoint(x, y);
}

QPoint SortingBox::randomItemPosition()
{
    return QPoint(qrand() % (width() - 120), qrand() % (height() - 120));
}

QColor SortingBox::initialItemColor()
{
    return QColor::fromHsv(((shapeItems.size() + 1) * 85) % 256, 255, 190);
}

QColor SortingBox::randomItemColor()
{
    return QColor::fromHsv(qrand() % 256, 255, 190);
}
