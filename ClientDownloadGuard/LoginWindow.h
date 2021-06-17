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
	void setUsernameAndPasswordText(QString& username, QString& password);

private:
	Ui::MainWindowClass ui;

	QSharedPointer<QNetworkReply> reply;

	QSharedPointer<Validator> usernameValidator;
	QSharedPointer<Validator> passwordValidator;


	void setupConnections();
	bool isUsernameAndPasswordValid();
private slots:
	void onLoginClick();
	void onQuitClick();
	void onRegisterClick();
	void onLoginResponse();
	void onError(QNetworkReply::NetworkError errorCode);
	void onCredentialsTextChanged();
};
