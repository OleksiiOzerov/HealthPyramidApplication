
#include "HealthPyramidMainWindow.hpp"
#include "HealthPyramidView.hpp"

#include <QtWidgets>

HealthPyramidMainWindow::HealthPyramidMainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setWindowTitle(tr("Health Pyramid"));
    readSettings();

    HealthPyramidView *healthPyramidView = new HealthPyramidView(this);
    setCentralWidget(healthPyramidView);
}

void HealthPyramidMainWindow::readSettings()
{
    QSettings settings("HealthOrganization", "HealthPyramid");
    QPoint pos = settings.value("pos", QPoint(100, 100)).toPoint();
    QSize size = settings.value("size", QSize(700, 600)).toSize();
    resize(size);
    move(pos);
}

void HealthPyramidMainWindow::writeSettings()
{
    QSettings settings("HealthOrganization", "HealthPyramid");
    settings.setValue("pos", pos());
    settings.setValue("size", size());
}

void HealthPyramidMainWindow::closeEvent(QCloseEvent *event)
{
    writeSettings();
    event->accept();
}
