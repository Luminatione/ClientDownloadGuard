#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_mainWindow.h"
#include <QtNetwork/QNetworkReply>

class LoginWindow : public QMainWindow
{
	Q_OBJECT

public:
	LoginWindow(QWidget* parent = Q_NULLPTR);

private:
	Ui::MainWindowClass ui;
	QNetworkAccessManager* networkAccessManager;
	QNetworkReply* reply;
#ifdef _DEBUG
	QString hostname = "http://localhost:5000/api/";
#else
	QString hostname = "http://192.168.1.10:5000/api/";
#endif
	QString loginPage = "login";

	void setupConnections();
private slots:
	void onLoginClick();
	void onQuitClick();
	void onRegisterClick();
	void onLoginResponse();
	void onError(QNetworkReply::NetworkError code);
};
