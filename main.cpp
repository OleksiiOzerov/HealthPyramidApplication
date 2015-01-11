#include <QtWidgets>

#include "sortingbox.h"

int main(int argc, char *argv[])
{
    //Q_INIT_RESOURCE(tooltips);

    QApplication application(argc, argv);

    application.setOrganizationName("HealthOrganization");
    application.setApplicationName("HealthPyramid");
    // qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    SortingBox sortingBox;
    sortingBox.show();

    return application.exec();
}
