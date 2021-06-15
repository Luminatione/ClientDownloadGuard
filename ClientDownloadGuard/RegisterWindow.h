#pragma once

#include <QWidget>
#include "ui_RegisterWindow.h"

class RegisterWindow : public QWidget
{
	Q_OBJECT

public:
	RegisterWindow(QWidget *parent = Q_NULLPTR);
	~RegisterWindow();

private:
	Ui::RegisterWindow ui;
};
