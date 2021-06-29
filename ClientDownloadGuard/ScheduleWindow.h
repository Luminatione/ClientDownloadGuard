#pragma once

#include <QFile>

#include "ScheduleRecord.h"

#include <QMainWindow>
#include <ui_ScheduleWindow.h>

class ScheduleWindow : public QMainWindow
{
	Q_OBJECT
	Ui::ScheduleWindow ui;
	QVector<ScheduleRecord> records;
	QFile file = QFile("schedule.dat");
	QDataStream dataStream = QDataStream(&file);

	void setupConnections();
	void loadRecords();
	void displayRecords();
	void addItemToList(QString& name);
	void saveRecords();
	void truncateFile();
	void closeFile();
	void setLayoutWidgetsEnabledState(bool state, QLayout* layout = nullptr);
	void closeEvent(QCloseEvent* event) override;
public:
	ScheduleWindow(QWidget* parent = nullptr);
	~ScheduleWindow();

private slots:
	void onAddClick();
	void onCloseClick();
	void onRemoveClick();
	void onSelectionChanged();
	void onConfirmClick();
	void onEditNameEnd();
};

