#include <QUrl>
#include <QTimer>
#include <QFile>
#include <QMap>
#include <QTextStream>
#include <QMainWindow>
#include <QLineEdit>
#include <QApplication>
#include <QPushButton>
#include <QFormLayout>
#include <QCheckBox>
#include <QSettings>
#include <QLabel>
#include <QObject>
#include "twitter.h"

class TwitterClient {

    /*
    Q_OBJECT

    */
    public:

    TwitterClient(QString configfile, QString ApiBase)
    {
        _timer = new QTimer();
        _mainwindow = new QWidget();

        _apibase = new QUrl();

        QFile config(configfile);
        QStringList list;

        if (!config.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        QTextStream in(&config);
        QString line = in.readLine();


        /*
        while (!line.isNull()) {
            list.append(line.split("="));
        }

        for( int i = 0; i < list.size(); i++){
            _map[list[i]] = _map[list[i + 1]];
        }

        */

        _mainwindow->show();
        _mainwindow->setGeometry(1368 / 2 , 100, 400, 600);
     // connect(_timer, &QTimer::timeout, this)
     //
        _username = new QLineEdit();

        _password = new QLineEdit();

        QFormLayout *_defaultlayout = new QFormLayout;

        _defaultlayout->addRow(QObject::tr("&Username:"), _username);
        _defaultlayout->addRow(QObject::tr("&Password"), _password);

        _defaultlayout->setRowWrapPolicy(QFormLayout::DontWrapRows);
        _defaultlayout->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);
        _defaultlayout->setFormAlignment(Qt::AlignCenter | Qt::AlignTop);
        _defaultlayout->setLabelAlignment(Qt::AlignLeft);

        _mainwindow->setLayout(_defaultlayout);
    }

    bool Authorize(QString ApiEndpoint) 
    {

    }

    void ClientLoop()
    {

    }

    ~TwitterClient()
    {
        delete _timer;

        delete _mainwindow;
        delete _centralWidget;

        delete _username;

        delete _password;

        delete _defaultlayout;
    }

    private:

        QMap<QString, QString> _map;

        QTimer *_timer;
        QUrl *_apibase;

        QWidget *_mainwindow;
        QLayout *_centralWidget;

        QLineEdit *_username;
        QString username;

        QLineEdit *_password;
        QString password;

        QGridLayout *_defaultlayout;

        QPushButton *_login;
        QCheckBox *_rememberme;

        QSettings *_settings;
};


int main(int argc, char **argv)
{
    QApplication *app = new QApplication(argc, argv);

    TwitterClient *Client = new TwitterClient(QString("config.conf"), QString("https://api.twitter.com"));

    //Client->Authorize(QString("oauth/authorize"));

    Client->ClientLoop();

    app->exec();
}
