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

	QSharedPointer<QNetworkReply> reply;

	bool isLoginValid = false;
	bool isPasswordValid = false;

	QSharedPointer<Validator> usernameValidator;
	QSharedPointer<Validator> passwordValidator;


	void setupConnections();
	bool isUsernameAndPasswordValid();
private slots:
	void onLoginClick();
	void onQuitClick();
	void onRegisterClick();
	void onLoginResponse();
	void onError(QNetworkReply::NetworkError code);
	void onCredentialsTextChanged();
};
