#include "../Headers/user.h"

// User::User() {}

void User::update(const QString &n, const QString &pass, const QString &id)
{
    name = n;
    password = pass;
    this->id = id;
    // role = r;
}
