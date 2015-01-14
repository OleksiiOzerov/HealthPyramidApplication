#include "DatabaseHandler.hpp"

#include <QSqlDatabase>

#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlQuery>

#include <QDate>
//#include <QDebug>

DatabaseHandler::DatabaseHandler()
{
}

bool DatabaseHandler::connectToDatabase()
{
    QSqlDatabase dataBase = QSqlDatabase::addDatabase("QSQLITE");
    dataBase.setDatabaseName("HealthPyramidApp");

    if (!dataBase.open())
    {
        return false;
    }

    QSqlQuery query;
    query.exec("create table pyramid (id varchar(20) primary key, "
               "firstitem int, seconditem int, thirditem int, fourthitem int, fifthitem int, sixitem int)");

    return true;
}


QList<int> DatabaseHandler::readPreviousSession()
{
    QSqlQueryModel plainModel;
    plainModel.setQuery("select * from pyramid");
    int rowCount = plainModel.rowCount();

    //qDebug() << "rosadwCount " << rowCount;

    QList<int> previousSession;
    if (rowCount != 0)
    {
        QSqlRecord record = plainModel.record(rowCount - 1);
        QString date = record.value("id").toString();

        if (date == QDate::currentDate().toString())
        {
            int firstitem = record.value("firstitem").toInt();
            int seconditem = record.value("seconditem").toInt();
            int thirditem = record.value("thirditem").toInt();
            int fourthitem = record.value("fourthitem").toInt();
            int fifthitem = record.value("fifthitem").toInt();
            int sixitem = record.value("sixitem").toInt();

//            qDebug() << "firstitem " << firstitem << "seconditem " << seconditem << "thirditem " << thirditem
//                     << "fourthitem " << fourthitem << "fifthitem " << fifthitem << "sixitem " << sixitem;

            previousSession.push_back(firstitem);
            previousSession.push_back(seconditem);
            previousSession.push_back(thirditem);
            previousSession.push_back(fourthitem);
            previousSession.push_back(fifthitem);
            previousSession.push_back(sixitem);
        }
    }
    return previousSession;
}

void DatabaseHandler::writeCurrentSession(QList<int> currentSession)
{
    QSqlQuery query;

    QString request = QString("insert into pyramid values('%1', %2, %3, %4, %5, %6, %7)").arg(QDate::currentDate().toString()).arg(currentSession[0]).arg(currentSession[1]).arg(currentSession[2]).arg(currentSession[3]).arg(currentSession[4]).arg(currentSession[5]);

    //qDebug() << request;

    query.exec(request);

}
void DatabaseHandler::updateCurrentSession(QList<int> currentSession)
{
    QSqlQuery query;
    query.prepare("update pyramid set firstitem = ? where id = ?");

    query.addBindValue(currentSession[0]);
    query.addBindValue(QDate::currentDate().toString());
    query.exec();

    query.prepare("update pyramid set seconditem = ? where id = ?");

    query.addBindValue(currentSession[1]);
    query.addBindValue(QDate::currentDate().toString());
    query.exec();

    query.prepare("update pyramid set thirditem = ? where id = ?");

    query.addBindValue(currentSession[2]);
    query.addBindValue(QDate::currentDate().toString());
    query.exec();

    query.prepare("update pyramid set fourthitem = ? where id = ?");

    query.addBindValue(currentSession[3]);
    query.addBindValue(QDate::currentDate().toString());
    query.exec();

    query.prepare("update pyramid set fifthitem = ? where id = ?");

    query.addBindValue(currentSession[4]);
    query.addBindValue(QDate::currentDate().toString());
    query.exec();

    query.prepare("update pyramid set sixitem = ? where id = ?");

    query.addBindValue(currentSession[5]);
    query.addBindValue(QDate::currentDate().toString());
    query.exec();
}
