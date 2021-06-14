#pragma once

#include "ui_mainWindow.h"
#include "Validator.h"

#include <QtWidgets/QMainWindow>
#include <QtNetwork/QNetworkReply>
#include <QSharedPointer>

class LoginWindow : public QMainWindow
{
	Q_OBJECT

public:
	LoginWindow(QWidget* parent = Q_NULLPTR);

private:
	Ui::MainWindowClass ui;

	QSharedPointer<QNetworkAccessManager> networkAccessManager;
	QSharedPointer<QNetworkReply> reply;

#ifdef _DEBUG
	QString hostname = "http://localhost:5000/api/";
#else
	QString hostname = "http://192.168.1.10:5000/api/";
#endif
	QString loginPage = "login";

	bool isLoginValid = false;
	bool isPasswordValid = false;

	QSharedPointer<Validator> usernameValidator;
	QSharedPointer<Validator> passwordValidator;


	void setupConnections();
private slots:
	void onLoginClick();
	void onQuitClick();
	void onRegisterClick();
	void onLoginResponse();
	void onError(QNetworkReply::NetworkError code);
	void onCredentialsTextChanged();
};
