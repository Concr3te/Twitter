#include <QApplication>
#include <QWebView>

int main(int argc, char **argv)
{
    QApplication *app = new QApplication(argc, argv);

    QWebView *view = new QWebView();
    view->load(QUrl("http://qt-project.org"));
    view->show();

    return app->exec();
}
