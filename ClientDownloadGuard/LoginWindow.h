#pragma once


#include <QtWidgets/QMainWindow>
#include <QtNetwork/QNetworkReply>
#include <QSharedPointer>

#include "ui_mainWindow.h"
#include "Validator.h"
#include "LoadingUtility.h"

class LoginWindow : public QMainWindow
{
	Q_OBJECT

public:
	LoginWindow(QWidget* parent = Q_NULLPTR);
	void setUsernameAndPasswordText(QString& username, QString& password);

private:
	Ui::MainWindowClass ui;

	QSharedPointer<QNetworkReply> reply;

	QSharedPointer<LoadingUtility> loading = QSharedPointer<LoadingUtility>(new LoadingUtility(this));

	QSharedPointer<Validator> usernameValidator;
	QSharedPointer<Validator> passwordValidator;


	void setupConnections();
	bool areUsernameAndPasswordValid();
private slots:
	void onLoginClick();
	void onQuitClick();
	void onRegisterClick();
	void onLoginResponse();
	void onError(QNetworkReply::NetworkError errorCode);
	void onCredentialsTextChanged();
};
