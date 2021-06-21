#pragma once
#include <QMainWindow>
#include <QNetworkReply>

#include "Validator.h"
#include "ui_registerWindow.h"


class RegisterWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	RegisterWindow(QWidget* parent = Q_NULLPTR);
	~RegisterWindow();

private:
	Ui::MainWindow ui;

	QSharedPointer<Validator> usernameValidator;
	QSharedPointer<Validator> passwordValidator;

	QSharedPointer<QNetworkReply> reply;
	
	void setupConnections();
	bool isUsernameAndPasswordValid();
private slots:
	void onQuitClick();
	void onLoginClick();
	void onRegisterClick();
	void openFilledLoginWindow();
	void onRegisterResponse();
	void onError(QNetworkReply::NetworkError errorCode);
	void onCredentialsTextChanged();
};
