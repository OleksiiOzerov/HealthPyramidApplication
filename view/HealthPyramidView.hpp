#ifndef HEALTHPYRAMIDVIEW_H
#define HEALTHPYRAMIDVIEW_H

#include "PyramidItem.hpp"
#include "PyramidItemPathFactory.hpp"

#include <QWidget>

QT_BEGIN_NAMESPACE
class QAction;
class QPoint;
class QToolButton;
QT_END_NAMESPACE

class HealthPyramidView : public QWidget
{
    Q_OBJECT

public:
    explicit HealthPyramidView(QWidget* parent = 0);

protected:
    bool event(QEvent *event) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    QPainterPath getItemPath(ItemPathType itemType);

    void createAllShapeItems();

    void createShapeItem(const QPainterPath &path,
                         const size_t GreenColorClickNumber,
                         const QString &toolTip,
                         const QPoint &pos,
                         const QColor &color,
                         const QBrush &brush);

    int itemAt(const QPoint &pos);

private:
    QPainterPath m_Background;

    QPoint m_ViewShift;

    QString m_DescriptionText;

    QList<PyramidItem> shapeItems;

    PyramidItem *itemInMotion;
};

#endif
