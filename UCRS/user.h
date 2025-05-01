#pragma once
#ifndef USER_H
#define USER_H
#include <QString>
#include <QDebug>
using namespace std;

enum UserRole  { ADMIN, INSTRUCTOR, STUDENT };

class User
{
protected:
    QString name;
    QString username;
    QString password;
    QString id;
    UserRole role;
public:
    User(const QString& n, const QString& uname, const QString& pass, const QString& id, UserRole r): name(n), username(uname), password(pass), id(id), role(r){};
    virtual ~User() = default;
    QString getName() const {return name;}
    QString getUsername() const {return username;}
    QString getPassword() const {return password;}
    UserRole getRole() const {return role;}
    QString getID() {return id;}
};

#endif // USER_H
