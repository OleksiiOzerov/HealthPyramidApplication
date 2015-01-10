
#include "sortingbox.h"
#include "utils.hpp"

#include <QtWidgets>
#include <stdlib.h>

SortingBox::SortingBox() : m_FoodPiramidFigureShift(0,0), m_InitialColor(255,0,0),
    m_GreenColorLevelCollection({0, 0, 0, 0, 0, 0, 0}),
    m_PressFigureCountCollection({0, 0, 0, 0, 0, 0, 0})
{
    initializeColorCollection();
    initializePressCountCollection();

    setWindowTitle(tr("Food Pyramid"));
    resize(700, 135 + 138 + 151 + 177);

    setMouseTracking(true);

    setBackgroundRole(QPalette::Base);

    itemInMotion = 0;

    createFirstLevelFigure();

    createSecondLevelLeftFigure();
    createSecondLevelRightFigure();

    createThirdLevelLeftFigure();
    createThirdLevelRightFigure();

    createForthLevelLeftFigure();


    m_Background.moveTo(0  , 0);
    m_Background.lineTo(700, 0);
    m_Background.lineTo(700, 135 + 138 + 151 + 177);
    m_Background.lineTo(0, 135 + 138 + 151 + 177);
    m_Background.lineTo(0, 0);

    createShapeItem(m_FirstLevelFigure,
                    tr("Fats, Oils, & Sweets"),
                    m_FoodPiramidFigureShift + QPoint(300, 0),
                    m_InitialColor,
                    QBrush(QPixmap(":/images/1.png")),
                    FigureType::firstFigure);

    createShapeItem(m_SecondLevelLeftFigure,
                    tr("Milk, Yogurt, & Cheese Group"),
                    m_FoodPiramidFigureShift + QPoint(217, 135),
                    m_InitialColor,
                    QBrush(QPixmap(":/images/2.png")),
                    FigureType::secondFigure);

    createShapeItem(m_SecondLevelRightFigure,
                    tr("Meat, Poultry, Fish, Dry Beans, Eggs, & Nuts Group"),
                    m_FoodPiramidFigureShift + QPoint(362, 135),
                    m_InitialColor,
                    QBrush(QPixmap(":/images/3.png")),
                    FigureType::thirdFigure);

    createShapeItem(m_ThirdLevelLeftFigure,
                    tr("Vegetable Group"),
                    m_FoodPiramidFigureShift + QPoint(138, 138 + 135),
                    m_InitialColor,
                    QBrush(QPixmap(":/images/4.png")),
                    FigureType::fourthFigure);

    createShapeItem(m_ThirdLevelRightFigure,
                    tr("Fruit Group"),
                    m_FoodPiramidFigureShift + QPoint(362, 138 + 135),
                    m_InitialColor,
                    QBrush(QPixmap(":/images/5.png")),
                    FigureType::fivthFigure);

    createShapeItem(m_ForthLevelFigure,
                    tr("Bread, Cereal, Rise, & Pasta Group"),
                    m_FoodPiramidFigureShift + QPoint(20, 151 + 138 + 135),
                    m_InitialColor,
                    QBrush(QPixmap(":/images/6.png")),
                    FigureType::sixthFigure);
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

    QFont font;
    font.setStyleHint(QFont::Courier, QFont::PreferAntialias);
    font.setPointSize(30);

   //painter.translate(QPoint(0, 0));
    painter.setPen(QPen(Qt::NoPen));
    painter.setBrush(QColor(255, 255, 255));

    painter.drawPath(m_Background);

    //painter.translate(QPoint(700, 135 + 138 + 151 + 177));

    foreach (ShapeItem shapeItem, shapeItems)
    {
        painter.translate(shapeItem.position());

        painter.setBrush(shapeItem.brush());
        painter.setPen(QPen(QColor(0, 0, 0)));
        painter.drawPath(shapeItem.path());

        painter.setFont(font);
        painter.setPen(shapeItem.pen());
        painter.drawText(40, 40, QString::number(shapeItem.clickNumber()));
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

           itemInMotion->itemClicked();

           if (greenColorNumberTypeMax == itemInMotion->clickNumber())
           {
              itemInMotion->setPen(QPen(QColor(0, 255, 0)));
              itemInMotion->setColor(QColor(0, 255, 0));
           }
           else if (greenColorNumberTypeMax / 2 == itemInMotion->clickNumber())
           {
              itemInMotion->setPen(QPen(QColor(255, 255, 0)));
              itemInMotion->setColor(QColor(255, 255, 0));
           }
           else if (itemInMotion->clickNumber() == 1)
           {
              itemInMotion->setPen(QPen(QColor(255, 0, 0)));
              itemInMotion->setColor(QColor(255, 0, 0));
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
    m_FirstLevelFigure.moveTo(46 , 0);
    m_FirstLevelFigure.lineTo(72 , 0);
    m_FirstLevelFigure.lineTo(125, 125);
    m_FirstLevelFigure.lineTo(125, 135);
    m_FirstLevelFigure.lineTo(0  , 135);
    m_FirstLevelFigure.lineTo(0  , 125);
    m_FirstLevelFigure.lineTo(46 , 0);
}

void SortingBox::createSecondLevelLeftFigure()
{
    m_SecondLevelLeftFigure.moveTo(62 , 0);
    m_SecondLevelLeftFigure.lineTo(147, 0);
    m_SecondLevelLeftFigure.lineTo(147, 138);
    m_SecondLevelLeftFigure.lineTo(0  , 138);
    m_SecondLevelLeftFigure.lineTo(62 , 0);
}

void SortingBox::createSecondLevelRightFigure()
{
    m_SecondLevelRightFigure.moveTo(0, 0);
    m_SecondLevelRightFigure.lineTo(66, 0);
    m_SecondLevelRightFigure.lineTo(139, 120);
    m_SecondLevelRightFigure.lineTo(139 ,138);
    m_SecondLevelRightFigure.lineTo(0, 138);
    m_SecondLevelRightFigure.lineTo(0, 0);
}

void SortingBox::createThirdLevelLeftFigure()
{
    m_ThirdLevelLeftFigure.moveTo(64 , 0);
    m_ThirdLevelLeftFigure.lineTo(230, 0);
    m_ThirdLevelLeftFigure.lineTo(230, 151);
    m_ThirdLevelLeftFigure.lineTo(0  , 151);
    m_ThirdLevelLeftFigure.lineTo(0  , 100);
    m_ThirdLevelLeftFigure.lineTo(64 , 0);
}

void SortingBox::createThirdLevelRightFigure()
{
    m_ThirdLevelRightFigure.moveTo(0, 0);
    m_ThirdLevelRightFigure.lineTo(150, 0);
    m_ThirdLevelRightFigure.lineTo(235, 100);
    m_ThirdLevelRightFigure.lineTo(235 ,151);
    m_ThirdLevelRightFigure.lineTo(0, 151);
    m_ThirdLevelRightFigure.lineTo(0, 0);
}

void SortingBox::createForthLevelLeftFigure()
{
    m_ForthLevelFigure.moveTo(95 , 0);
    m_ForthLevelFigure.lineTo(575, 0);
    m_ForthLevelFigure.lineTo(671, 148);
    m_ForthLevelFigure.lineTo(671, 177);
    m_ForthLevelFigure.lineTo(0  , 177);
    m_ForthLevelFigure.lineTo(0  , 144);
    m_ForthLevelFigure.lineTo(95 , 0);
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
                                 const QColor &color, const QBrush &brush,
                                 FigureType type)
{
    ShapeItem shapeItem;
    shapeItem.setPath(path);
    shapeItem.setToolTip(toolTip);
    shapeItem.setPosition(pos);
    shapeItem.setColor(color);
    shapeItem.setBrush(brush);
    shapeItem.setType(type);
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
