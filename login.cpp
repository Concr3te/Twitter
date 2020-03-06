#include "login.h"

Login::Login(QString username, QString password)
{
    username = username;
    password = password;
}

QString Login::username()
{
    return username;
}

QString Login::password()
{
    return password;
}
