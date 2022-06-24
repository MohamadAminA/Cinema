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
    bool AddMovie(Movie);
    QList<Movie> *GetMovies();
    bool ValidateAdmin(User);
    void CreateAdmin(User);
    bool RemoveMovie(QString);
    void UpdateMovie(Movie);
};

#endif // DBUTIL_H
