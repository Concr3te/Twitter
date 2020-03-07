#include <QUrl>
#include <QNetworkRequest>
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
#include <string>
#include "twitter.h"
#include "login.h"

class OAuth2Details {

    public:
        OAuth2Details(QString file);

        QString OAuthToken();
        QString OAuthTokenSecret();

        QString OAuthConsumerKey();
        QString OAuthConsumerSecret();

    private:
        QString oauth_token;
        QString oauth_token_secret;

        QString oauth_consumer_key;
        QString oauth_consumer_secret;
};

QString OAuth2Details::OAuthToken()
{
    return oauth_token;
}

QString OAuth2Details::OAuthTokenSecret()
{
    return oauth_token_secret;
}

QString OAuth2Details::OAuthConsumerKey()
{
    return oauth_consumer_key;
}

QString OAuth2Details::OAuthConsumerSecret()
{
    return oauth_consumer_secret;
}

OAuth2Details::OAuth2Details(QString file)
{
    QFile config(file);
    QString line;

    if (!config.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&config);

    while ((line = in.readLine())
    {
        //search for the said string
        std::string temp = line.toStdString();
        if(temp.find("oauth_consumer_key") != std::string::npos) {
            QStringList list = temp.split("=");
            if (list.size() = 2) {
                this->oauth_consumer_key = list[1];
            }
        } else if(temp.find("oauth_consumer_secret") != std::string::npos)
        {
            QStringList list = temp.split("=");
            if (list.size() = 2) {
                this->oauth_consumer_secret = list[1];
            }

        } else if (temp.find("oauth_token") != std::string::npos)
        {
            QStringList list = temp.split("=");
            if (list.size() = 2) {
                this->oauth_token = list[1];
            }
        } else if (temp.find("oauth_token_secret") != std::string::npos)
        {
            QStringList list = temp.split("=");
            if (list.size() = 2) {
                this->oauth_token_secret = list[1];
            }
        }
        else{
            //qDebug<<temp;
            ;
        }
    }
}


class TwitterSettings : public QSettings
{
    public:

    private:
        Login *login;
};

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

        _mainwindow->show();
        _mainwindow->setGeometry(1368 / 2 , 100, 400, 600);
     // connect(_timer, &QTimer::timeout, this)
     //
        _username = new QLineEdit();

        _password = new QLineEdit();

        _login = new QPushButton();
        _login->setText("Login");
        //_login->setColor(QColor::Blue);

        QFormLayout *_defaultlayout = new QFormLayout;

        _defaultlayout->addRow(QObject::tr("&Username:"), _username);
        _defaultlayout->addRow(QObject::tr("&Password"), _password);
        _defaultlayout->addRow(_login);
        _defaultlayout->addRow(_rememberme);

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
