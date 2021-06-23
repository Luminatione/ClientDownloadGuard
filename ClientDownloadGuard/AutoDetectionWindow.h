#pragma once
#include <QComboBox>
#include <qmainwindow.h>
#include <QTreeWidgetItem>
#include "ui_AutoDetctionWindow.h"
class AutoDetectionWindow : public QMainWindow
{
	Q_OBJECT
	
	Ui::AutoDetectionWindow ui;
public:
	AutoDetectionWindow(QWidget* parent = nullptr);
private:
	QComboBox* getComboBoxWithItems(QStringList& items);
	QComboBox* getTypeComboBox();
	QComboBox* getConflictBehaviourComboBox();
	void loadTableContent();
	void loadLayout();
	void saveLayout();
	void saveTableContent();
	void setupConnections();
private slots:
	void onAddClick();
	void onOkClick();
	void onCancelClick();
};

