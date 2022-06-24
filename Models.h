#ifndef MODELS_H
#define MODELS_H

#include <QString>

class User {
public:
    User(QString uname, QString pass) : username{uname}, password{pass} {}
    int id;
    QString username;
    QString password;
};

class Movie {
public:
    int id;
    QString name;
    int tickets;
    int bookedTickets;
    QString time;
    QString genre;
    QString releaseDate;
    QString director;
    QString moviecast;
    double imdb;
    Movie(QString name, int tickets, int bookedTickets, QString time, QString genre,
          QString releaseDate, QString director, QString moviecast, double imdb) : name{name}, tickets{tickets}
      , bookedTickets{bookedTickets}, time{time}, genre{genre}, releaseDate{releaseDate}, director{director},
        moviecast{moviecast}, imdb{imdb} {  }
};

#endif // MODELS_H
