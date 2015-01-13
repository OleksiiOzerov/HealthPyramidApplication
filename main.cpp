
#include "view/HealthPyramidMainWindow.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    application.setOrganizationName("HealthOrganization");
    application.setApplicationName("HealthPyramid");

    HealthPyramidMainWindow healthPyramidMainWindow;
    healthPyramidMainWindow.show();

    return application.exec();
}
