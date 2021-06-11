#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_mainWindow.h"

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    LoginWindow(QWidget *parent = Q_NULLPTR);

private:
    Ui::MainWindowClass ui;

    void setupConnections();
private slots:
    void onLoginClick();
    void onQuitClick();
    void onRegisterClick();
};
