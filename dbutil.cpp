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
        q.exec("CREATE TABLE users (id INTEGER PRIMARY KEY AUTOINCREMENT, username VARCHAR(255) UNIQUE NOT NULL, password VARCHAR(255) NOT NULL);");
        q.clear();
        q.exec("CREATE TABLE admins (id INTEGER PRIMARY KEY AUTOINCREMENT, username VARCHAR(255) UNIQUE NOT NULL, password VARCHAR(255) NOT NULL);");
        q.clear();
        q.exec("CREATE TABLE reserves (id INTEGER PRIMARY KEY AUTOINCREMENT, username VARCHAR(255) NOT NULL, movie VARCHAR(255) NOT NULL);");
        q.clear();
        q.exec("CREATE TABLE movies (id INTEGER PRIMARY KEY AUTOINCREMENT, name VARCHAR(255) UNIQUE NOT NULL, tickets INTEGER, bookedTickets INTEGER, time TEXT, genre VARCHAR(255), releaseDate TEXT, director VARCHAR(255), moviecast TEXT, imdb REAL);");
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

bool dbutil::AddMovie(Movie movie) {
    db.open();
    QSqlQuery q;
    q.prepare("INSERT INTO movies (name, tickets, bookedTickets, time, genre, releaseDate, director, moviecast, imdb) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?);");
    q.addBindValue(movie.name);
    q.addBindValue(movie.tickets);
    q.addBindValue(movie.bookedTickets);
    q.addBindValue(movie.time);
    q.addBindValue(movie.genre);
    q.addBindValue(movie.releaseDate);
    q.addBindValue(movie.director);
    q.addBindValue(movie.moviecast);
    q.addBindValue(movie.imdb);
    q.exec();
    QSqlError err = q.lastError();
    if (err.isValid()) {
        q.clear();
        db.close();
        return false;
    } else {
        q.clear();
        db.close();
        return true;
    }
}

QList<Movie> *dbutil::GetMovies() {
    db.open();
    QSqlQuery q;
    q.prepare("SELECT * FROM movies;");
    q.exec();
    QList<Movie> *list = new QList<Movie>();
    while (q.next()) {
        Movie mov{q.value(1).toString(),
                 q.value(2).toInt(),
                 q.value(3).toInt(),
                 q.value(4).toString(),
                 q.value(5).toString(),
                 q.value(6).toString(),
                 q.value(7).toString(),
                 q.value(8).toString(),
                 q.value(9).toDouble()};
        list->append(mov);
    }
    return list;
}

bool dbutil::ValidateAdmin(User admin) {
    if (!admin.username.compare("admin") && !admin.password.compare("123456")) return true;
    db.open();
    QSqlQuery q;
    q.prepare("SELECT * FROM admins WHERE username=?;");
    q.addBindValue(admin.username);
    q.exec();
    bool exists = q.next();
    if (exists) {
        QString pass = q.value(2).toString();
        bool verify = !pass.compare(admin.password);
        q.clear();
        db.close();
        return verify;
    }
    q.clear();
    db.close();
    return exists;
}

bool dbutil::RemoveMovie(QString moviename) {
    db.open();
    QSqlQuery q;
    q.prepare("DELETE FROM movies WHERE name=?;");
    q.addBindValue(moviename);
    q.exec();
    q.clear();
    db.close();
    return true;
}



