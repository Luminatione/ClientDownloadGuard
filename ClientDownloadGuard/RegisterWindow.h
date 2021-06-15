#pragma once

#include <QWidget>
#include <QNetworkReply>

#include "ui_RegisterWindow.h"
#include "Validator.h"

class RegisterWindow : public QWidget
{
	Q_OBJECT

public:
	RegisterWindow(QWidget *parent = Q_NULLPTR);
	~RegisterWindow();

private:
	Ui::RegisterWindow ui;

	bool isLoginValid = false;
	bool isPasswordValid = false;

	QSharedPointer<Validator> usernameValidator;
	QSharedPointer<Validator> passwordValidator;

	QSharedPointer<QNetworkReply> reply;

	void setupConnections();
	bool isUsernameAndPasswordValid();
private slots:
	void onQuitClick();
	void onLoginClick();
	void onRegisterClick();
	void onRegisterResponse();
	void onError(QNetworkReply::NetworkError errorCode);
	void onCredentialsChange();
};
