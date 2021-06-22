#include "LoginWindow.h"
#include <QtWidgets/QApplication>

#include "ServerConnectionManager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName("DownloadGuard");
    QCoreApplication::setOrganizationName("Luminatione");
    ServerConnectionManager::serverConnectionManager->syncWithSettings();
    LoginWindow w;
    w.show();
    return a.exec();
}
