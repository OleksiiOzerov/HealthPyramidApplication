
#include "HealthPyramidView.hpp"

#include <QtWidgets>
#include <stdlib.h>

HealthPyramidView::HealthPyramidView(QWidget* parent) : QWidget(parent),
    m_ViewShift(0,0)
{
    setMouseTracking(true);

    setBackgroundRole(QPalette::Light);

    m_Background.moveTo(0  , 0);
    m_Background.lineTo(700, 0);
    m_Background.lineTo(700, 135 + 138 + 151 + 177);
    m_Background.lineTo(0, 135 + 138 + 151 + 177);
    m_Background.lineTo(0, 0);

    createAllShapeItems();
}

void HealthPyramidView::setPreviousSession(QList<int> previousSession)
{
    for (int i = 0; i < previousSession.size(); ++i)
    {
        for(int j = 0; j < previousSession[i]; ++j)
        {
            shapeItems[i].itemClicked();
        }
    }
}

QList<int> HealthPyramidView::getCurrentSession()
{
    QList<int> currentSession;

    for(int i = 0; i < shapeItems.size(); ++i)
    {
        currentSession.push_back(shapeItems[i].clickNumber());
    }

    return currentSession;

}

bool HealthPyramidView::event(QEvent *event)
{
    if (event->type() == QEvent::ToolTip)
    {
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

void HealthPyramidView::resizeEvent(QResizeEvent * /* event */)
{
}

void HealthPyramidView::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QFont font;
    font.setStyleHint(QFont::Courier, QFont::PreferAntialias);
    font.setPointSize(30);

    painter.setPen(QPen(Qt::NoPen));
    painter.setBrush(QColor(255, 255, 255));
    painter.drawPath(m_Background);

    painter.setPen(QPen(Qt::SolidLine));
    painter.drawText(10, 10, m_DescriptionText);

    foreach (PyramidItem shapeItem, shapeItems)
    {
        painter.translate(shapeItem.position());

        painter.setBrush(shapeItem.brush());
        painter.setPen(QPen(Qt::NoPen));
        painter.drawPath(shapeItem.path());

        painter.setFont(font);
        painter.setPen(shapeItem.pen());
        painter.drawText(70, 50, QString::number(shapeItem.clickNumber()));
        painter.translate(-shapeItem.position());
    }
}

void HealthPyramidView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        int index = itemAt(event->pos());
        if (index != -1)
        {
           itemInMotion = &shapeItems[index];

           itemInMotion->itemClicked();

            update();
        }
    }
}

void HealthPyramidView::mouseMoveEvent(QMouseEvent *event)
{
    int index = itemAt(event->pos());

    if (index != -1)
    {
        itemInMotion = &shapeItems[index];

        m_DescriptionText = itemInMotion->toolTip();

        update();
    }
}


QPainterPath HealthPyramidView::getItemPath(ItemPathType itemType)
{
    return PyramidItemPathFactory::getItemPath(itemType);

}

int HealthPyramidView::itemAt(const QPoint &pos)
{
    for (int i = shapeItems.size() - 1; i >= 0; --i)
    {
        const PyramidItem &item = shapeItems[i];
        if (item.path().contains(pos - item.position()))
            return i;
    }
    return -1;
}

void HealthPyramidView::createAllShapeItems()
{
    createShapeItem(getItemPath(firstItemPath), 1,
                    tr("Fats, Oils, & Sweets"),
                    m_ViewShift + QPoint(300, 0),
                    QColor(255, 0, 0),
                    QBrush(QPixmap(":/images/1.png")));

    createShapeItem(getItemPath(secondItemPath), 3,
                    tr("Milk, Yogurt, & Cheese Group"),
                    m_ViewShift + QPoint(217, 135),
                    QColor(255, 0, 0),
                    QBrush(QPixmap(":/images/2.png")));

    createShapeItem(getItemPath(thirdItemPath), 3,
                    tr("Meat, Poultry, Fish, Dry Beans, Eggs, & Nuts Group"),
                    m_ViewShift + QPoint(363, 135),
                    QColor(255, 0, 0),
                    QBrush(QPixmap(":/images/3.png"))/*,
                    FigureType::thirdFigure*/);

    createShapeItem(getItemPath(fourthItemPath), 5,
                    tr("Vegetable Group"),
                    m_ViewShift + QPoint(137, 273),
                    QColor(255, 0, 0),
                    QBrush(QPixmap(":/images/4.png")));

    createShapeItem(getItemPath(fivthItemPath), 3,
                    tr("Fruit Group"),
                    m_ViewShift + QPoint(367, 273),
                    QColor(255, 0, 0),
                    QBrush(QPixmap(":/images/5.png")));

    createShapeItem(getItemPath(sixthItemPath), 11,
                    tr("Bread, Cereal, Rise, & Pasta Group"),
                    m_ViewShift + QPoint(30, 424),
                    QColor(255, 0, 0),
                    QBrush(QPixmap(":/images/6.png")));
}

void HealthPyramidView::createShapeItem(const QPainterPath &path,
                                 const size_t GreenColorClickNumber,
                                 const QString &toolTip,
                                 const QPoint &pos,
                                 const QColor &color,
                                 const QBrush &brush)
{
    PyramidItem shapeItem(GreenColorClickNumber);
    shapeItem.setPath(path);
    shapeItem.setToolTip(toolTip);
    shapeItem.setPosition(pos);
    shapeItem.setColor(color);
    shapeItem.setBrush(brush);
    shapeItems.append(shapeItem);
}
