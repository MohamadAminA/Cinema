#include "dbutil.h"
#include <QDir>
#include <QFile>
#include <QSqlQuery>
#include <QSqlError>

dbutil::dbutil()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    QString path = QDir().absolutePath() + "/database.sqlite";
    db.setDatabaseName(path);
    if (!QFile::exists(path)) {
        db.open();
        QSqlQuery q;
        q.exec("CREATE TABLE users (id INTEGER PRIMARY KEY AUTOINCREMENT, username VARCHAR(255) UNIQUE NOT NULL, password VARCHAR(255));");
        q.clear();
        q.exec("CREATE TABLE reserves (id INTEGER PRIMARY KEY AUTOINCREMENT, username VARCHAR(255) NOT NULL, movie VARCHAR(255) NOT NULL);");
        q.clear();
        db.close();
    }
}

bool dbutil::CreateUser(User user) {
    db.open();
    QSqlQuery q;
    q.prepare("INSERT INTO users (username, password) VALUES (?, ?);");
    q.addBindValue(user.username);
    q.addBindValue(user.password);
    q.exec();
    QSqlError err = q.lastError();
    if (err.isValid()) {
        q.clear();
        db.close();
        return false;
    }
    else {
        q.clear();
        db.close();
        return true;
    }
}

bool dbutil::ValidateUser(User user) {
    db.open();
    QSqlQuery q;
    q.prepare("SELECT * FROM users WHERE username=?;");
    q.addBindValue(user.username);
    q.exec();
    bool exists = q.next();
    if (exists) {
        QString pass = q.value(2).toString();
        bool verify = !pass.compare(user.password);
        q.clear();
        db.close();
        return verify;
    }
    q.clear();
    db.close();
    return exists;
}

bool dbutil::AddReserve(User user, QString moviename) {
    db.open();
    QSqlQuery q;
    q.prepare("SELECT * FROM reserves WHERE username=? AND movie=?;");
    q.addBindValue(user.username);
    q.addBindValue(moviename);
    q.exec();
    bool exists = q.next();
    q.clear();
    if (exists) {
        db.close();
        return !exists;
    } else {
        q.prepare("INSERT INTO reserves (username, movie) VALUES (?, ?);");
        q.addBindValue(user.username);
        q.addBindValue(moviename);
        q.exec();
        q.clear();
        db.close();
        return !exists;
    }
}

QList<QString> *dbutil::GetReserveList(User user) {
    db.open();
    QSqlQuery q;
    q.prepare("SELECT * FROM reserves WHERE username=?;");
    q.addBindValue(user.username);
    q.exec();
    QList<QString> *list = new QList<QString>();
    while (q.next())
        list->append(q.value(2).toString());
    q.clear();
    db.close();
    return list;
}

void dbutil::DeleteReserve(User user, QString moviename) {
    db.open();
    QSqlQuery q;
    q.prepare("DELETE FROM reserves WHERE username=? AND movie=?;");
    q.addBindValue(user.username);
    q.addBindValue(moviename);
    q.exec();
    q.clear();
    db.close();
}



