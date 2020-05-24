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
#include <QDate>
#include <string>
#include <QObject>
#include "twitter.h"
#include "login.h"

#define API_ENDPOINT_ROOT "api.twitter.com/v1.1"

class RequestLogin {

};

class ProfileSettings
{

};

class UserList : public QObject
{
    Q_OBJECT

   public:

     UserList()
     {
         this->widget = new QWidget;
     }

   private:

     QWidget *widget;
};

class TweetWidget : public QObject
{
    Q_OBJECT

   public:

    TweetWidget()
    {
        this->widget = new QWidget;
    }

   private:
    QWidget *widget;
};

class OAuth2Details
{

    public:
        OAuth2Details(QString file);

        QString *OAuthToken();
        QString *OAuthTokenSecret();
        QString *OAuthConsumerKey();
        QString *OAuthConsumerSecret();

        ~OAuth2Details();

    private:
        QString *oauth_token;
        QString *oauth_token_secret;

        QString *oauth_consumer_key;
        QString *oauth_consumer_secret;
};

OAuth2Details::OAuth2Details(QString file)
{
    QFile config(file);
    QString line;

    if (!config.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&config);

    while (!in.atEnd())
    {
        line = in.readLine();

        //search for the said string
        std::string temp = line.toStdString();
        if(temp.find("oauth_consumer_key") != std::string::npos) {
            QStringList list = line.split("=");
            if (list.size() == 2) {
                this->oauth_consumer_key = new QString(list.at(1));
            }
        } else if(temp.find("oauth_consumer_secret") != std::string::npos)
        {
            QStringList list = line.split("=");
            if (list.size() == 2) {
                this->oauth_consumer_secret = new QString(list.at(1));
            }

        } else if (temp.find("oauth_token") != std::string::npos)
        {
            QStringList list = line.split("=");
            if (list.size() == 2) {
                this->oauth_token = new QString(list.at(1));
            }
        } else if (temp.find("oauth_token_secret") != std::string::npos)
        {
            QStringList list = line.split("=");
            if (list.size() == 2) {
                this->oauth_token_secret = new QString(list.at(1));
            }
        }
        else{
            //qDebug<<temp;
            ;
        }
    }
}

class Tweet
{

  public:
    Tweet(int id, QString text)
        : id(new int(id)), text(new QString(text))
    {

    }

    bool Post(OAuth2Details *Details)
    {
        return true;
    }

    bool Get(int id, OAuth2Details *Details)
    {
        return true;
    }

    bool Delete(int id, OAuth2Details *Details)
    {
        return true;
    }

    bool Favourite(int id, OAuth2Details *Details)
    {
        return true;
    }

    bool Retweet(int id, OAuth2Details *Details)
    {
        return true;
    }

    ~Tweet()
    {
        delete this->id;
        delete this->text;
    }

private:

    int *id;
    QString *text;
    //QImage  *image;
    //QVideo *video;
};

class ProfileEditWidget : public QObject
{
    Q_OBJECT

  public:

    ProfileEditWidget()
    {
        this->widget = new QWidget;
    }

  private:

    QWidget *widget;
};

class Profile
{

public:
    Profile(QString handle)
    {
        this->handle = new QString(handle);
        this->followers = nullptr;
        this->following = nullptr;

        this->Bio = nullptr;
        this->name = nullptr;

        this->location = nullptr;
        this->handle = nullptr;
        this->birth_date = nullptr;
    }

    bool Get()
    {
        return true;
    }

    bool Edit()
    {
        return true;
    }

    ~Profile()
    {
        delete this->followers;
        delete this->following;
        delete this->Bio;

        delete this->name;
        delete this->location;
        delete this->handle;

        delete this->birth_date;
    }

private:

    int *followers;
    int *following;
    QString *Bio;
    QString *name;
    QString *location;
    QString *handle;
    QDate *birth_date;
};

QString *OAuth2Details::OAuthToken()
{
    return oauth_token;
}

QString *OAuth2Details::OAuthTokenSecret()
{
    return oauth_token_secret;
}

QString *OAuth2Details::OAuthConsumerKey()
{
    return oauth_consumer_key;
}

QString *OAuth2Details::OAuthConsumerSecret()
{
    return oauth_consumer_secret;
}

OAuth2Details::~OAuth2Details()
{
    delete this->oauth_token;
    delete this->oauth_token_secret;
    delete this->oauth_consumer_key;
    delete this->oauth_consumer_secret;
}


class TwitterSettings : public QSettings
{
    public:

    private:
        Login *login;
};

/*
class LoginButton : public QObject
{
    Q_OBJECT

  public:
    LoginButton(QString ButtonTag)
    {
        this->button = new QPushButton();
        QPushButton->setText(ButtonTag);


        connect(this, QPushButton::clicked(), this, ()[=])
    }

  private:

    QPushButton *button;
};

*/

class TwitterClient : public QObject
{
    /*
    Q_OBJECT

    */
    public:
    TwitterClient()
    {

    }

    TwitterClient(QString configfile, QString ApiBase)
    {
        _timer = new QTimer();
        _mainwindow = new QWidget();

        _apibase = new QUrl(ApiBase);

        QFile config(configfile);
        QStringList list;

        if (!config.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        QTextStream in(&config);
        QString line = in.readLine();

        _mainwindow->show();
        _mainwindow->setGeometry(1368 / 2 , 100, 400, 600);
        //connect(_timer, &QTimer::timeout, this)

        QObject::connect(_login, &QPushButton::clicked, this, [=]()
        {
            QString username = this->_username->text();
            QString password = this->_password->text();

            /*
             *
             * QWebView *view = new QWebView();
             *
             * view->load(QUrl("authorize_url"));
             * view->show();
             *
             */
        }
        );

       _username = new QLineEdit();

       _password = new QLineEdit();
       _password->setEchoMode(QLineEdit::Password);

        _login = new QPushButton();
        _login->setText("Login");
        //_login->setColor(QColor::Blue);

        _rememberme = new QCheckBox();

        _settings = new QSettings();
        _settings->setValue("rememberme", true);

        QObject::connect(_rememberme, &QCheckBox::clicked, this, [=]()
        {
            if(_settings->value("rememberme").toBool())
            {
                this->_settings->setValue("rememberme", true);
            }
            else
            {
                this->_settings->setValue("rememberme", false);
            }
        }
        );

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
        return 0;
    }

    void Stream()
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

     signals:

     public slots:


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

    Client->Authorize(QString("oauth/authorize"));

    Client->Stream();

    app->exec();
}
