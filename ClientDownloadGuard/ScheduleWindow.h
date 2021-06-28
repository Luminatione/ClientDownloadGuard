#pragma once

#include <QMainWindow>
#include <ui_ScheduleWindow.h>

class ScheduleWindow : public QMainWindow
{
	Ui::ScheduleWindow ui;

public:
	ScheduleWindow(QWidget* parent = nullptr);
};

