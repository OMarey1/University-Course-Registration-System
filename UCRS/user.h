#ifndef USER_H
#define USER_H
#include <QString>

enum UserRole  { ADMIN, INSTRUCTOR, STUDENT };

class User
{
protected:
    QString name;
    QString username;
    QString password;
    UserRole role;
public:
    User(QString n, QString uname, QString pass, UserRole r): name(n), username(uname), password(pass), role(r){};
    QString getName() const {return name;}
    QString getUsername() const {return username;}
    QString getPassword() const {return password;}
    UserRole getRole() const {return role;}
};

#endif // USER_H
