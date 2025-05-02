#ifndef ADMIN_H
#define ADMIN_H

#include "user.h"
using namespace std;

class Admin : public User
{
public:
    Admin(const QString& n, const QString& uname, const QString& pass, const QString& id):  User(n, uname, pass, id, ADMIN){};
};

#endif // ADMIN_H
