#pragma once
#include <QComboBox>
#include <qmainwindow.h>
#include <QTreeWidgetItem>

#include "ui_AutoDetctionWindow.h"
#include "AutoDetectionIO.h"

class AutoDetectionWindow : public QMainWindow
{
	Q_OBJECT
	
	Ui::AutoDetectionWindow ui;
	AutoDetectionIO autoDetectionIO = AutoDetectionIO();
public:
	AutoDetectionWindow(QWidget* parent = nullptr);
private:
	QComboBox* getComboBoxWithItems(QStringList& items);
	QComboBox* getTypeComboBox();
	QComboBox* getConflictBehaviourComboBox();
	
	void setIndexAtColumnAsComboBox(int column, int value);
	void readRecord();
	void loadTableContent();
	void loadLayout();
	void saveLayout();
	void saveTableContent();
	void setupConnections();
	int getCurrentIndexOfCellWidgetAsComboBox(int row, int column);
signals:
	void closeEvent(QCloseEvent* event) override;
private slots:
	void onAddClick();
	void onOkClick();
	void onCancelClick();
	void onRemoveClick();
};

