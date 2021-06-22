#include "LoginWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName("DownloadGuard");
    QCoreApplication::setOrganizationName("Luminatione");
    LoginWindow w;
    w.show();
    return a.exec();
}
