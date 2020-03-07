#ifndef _LOGIN_H
#define _LOGIN_H

class Login {

    public:
        Login(QString username, QString password);

        QString Username();

        QString Password();

    private:

        QString username;
        QString password;

};

#endif
