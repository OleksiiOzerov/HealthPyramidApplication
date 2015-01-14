#ifndef DATABASEHANDLER_HPP
#define DATABASEHANDLER_HPP

#include <QList>

class DatabaseHandler
{
public:
    DatabaseHandler();

    static bool connectToDatabase();

    static QList<int> readPreviousSession();

    static void writeCurrentSession(QList<int> currentSession);

    static void updateCurrentSession(QList<int> currentSession);
};

#endif // DATABASEHANDLER_HPP
