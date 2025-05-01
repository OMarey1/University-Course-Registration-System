#include "admin.h"
#include <cctype>
// Admin::Admin() {}

bool Admin::validatePassword(const QString &pass)
{
    if (pass.length() != 8) {
        return false;
    }

    for (const QChar c: pass){
        if (!isalnum(c.toLatin1())){
            return false;
        }
    }
    return true;
}
