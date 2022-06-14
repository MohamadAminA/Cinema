#ifndef DBUTIL_H
#define DBUTIL_H
#include "Models.h"
#include <QSqlDatabase>
#include <QString>
#include <QList>

class dbutil
{
private:
    QSqlDatabase db;
public:
    dbutil();
    bool CreateUser(User);
    bool ValidateUser(User);
    bool AddReserve(User, QString);
    QList<QString> *GetReserveList(User);
    void DeleteReserve(User, QString);
};

#endif // DBUTIL_H
