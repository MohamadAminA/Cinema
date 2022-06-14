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

#endif // MODELS_H
