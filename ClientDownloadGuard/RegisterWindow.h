#pragma once
#include <QMainWindow>
#include <QNetworkReply>


#include "LoadingUtility.h"
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

	QSharedPointer<LoadingUtility> loading = QSharedPointer<LoadingUtility>(new LoadingUtility(this));

	void setupConnections();
	bool isUsernameAndPasswordValid();
private slots:
	void onQuitClick();
	void onLoginClick();
	void onRegisterClick();
	void onRegisterResponse();
	void onError(QNetworkReply::NetworkError errorCode);
	void onCredentialsTextChanged();
};
