#ifndef HEALTHPYRAMIDMAINWINDOW_HPP
#define HEALTHPYRAMIDMAINWINDOW_HPP

#include <QMainWindow>

class HealthPyramidMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit HealthPyramidMainWindow(QWidget *parent = 0);

protected:
     void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

signals:

public slots:

private:
    void readSettings();
    void writeSettings();

};

#endif // HEALTHPYRAMIDMAINWINDOW_HPP
