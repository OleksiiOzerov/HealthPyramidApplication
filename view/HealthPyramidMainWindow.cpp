#include "../model/DatabaseHandler.hpp"
#include "HealthPyramidMainWindow.hpp"
#include "HealthPyramidView.hpp"

#include <QtWidgets>

HealthPyramidMainWindow::HealthPyramidMainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_WriteSession(true)
{
    setWindowTitle(tr("Health Pyramid"));
    readSettings();

    if(!DatabaseHandler::connectToDatabase())
    {
        QMessageBox::critical(0, tr("Cannot open database"),
                  tr("Unable to establish a database connection.\n"
                     "This example needs SQLite support. Please read "
                     "the Qt SQL driver documentation for information how "
                     "to build it.\n\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
    }

    QList<int> previousSession = DatabaseHandler::readPreviousSession();

    m_HealthPyramidView = new HealthPyramidView(this);

    if(!previousSession.empty())
    {
        m_WriteSession = false;
        m_HealthPyramidView->setPreviousSession(previousSession);
    }

    setCentralWidget(m_HealthPyramidView);
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

    if(m_WriteSession)
    {
        QList<int> currentSession = m_HealthPyramidView->getCurrentSession();
        DatabaseHandler::writeCurrentSession(currentSession);
    }
    else
    {
        QList<int> currentSession = m_HealthPyramidView->getCurrentSession();
        DatabaseHandler::updateCurrentSession(currentSession);
    }
    event->accept();
}
