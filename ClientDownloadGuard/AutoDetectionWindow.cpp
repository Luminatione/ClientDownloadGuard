#include "AutoDetectionWindow.h"
#include "QtMacros.h"
#include "DefaultSettings.h"

#include <QTreeWidget>
#include <QComboBox>
#include <QSettings>

AutoDetectionWindow::AutoDetectionWindow(QWidget* parent) : QMainWindow(parent)
{
	ui.setupUi(this);
	setupConnections();
	loadLayout();
	loadTableContent();
}

void AutoDetectionWindow::setupConnections()
{
	BUTTON_CLICK_TO_THIS_CONNECTION(ui.addButton, onAddClick());
	BUTTON_CLICK_TO_THIS_CONNECTION(ui.okButton, onOkClick());
	BUTTON_CLICK_TO_THIS_CONNECTION(ui.cancelButton, onCancelClick());
}

QComboBox* AutoDetectionWindow::getComboBoxWithItems(QStringList& items)
{
	QComboBox* comboBox = new QComboBox();
	comboBox->addItems(items);
	return comboBox;
}

QComboBox* AutoDetectionWindow::getTypeComboBox()
{
	QStringList options{"Free", "Downloading", "Ask not to download"};
	return getComboBoxWithItems(options);
}

QComboBox* AutoDetectionWindow::getConflictBehaviourComboBox()
{
	QStringList options{"Ignore", "Notify me", "Abandon"};
	return getComboBoxWithItems(options);
}

void AutoDetectionWindow::loadTableContent()
{
	
}

void AutoDetectionWindow::loadLayout()
{
	QSettings settings = QSettings();
	ui.tableWidget->setColumnWidth(0, settings.value("column0width", DefaultSettings::settings->autoDetectionTableColumnWidth).toInt());
	ui.tableWidget->setColumnWidth(1, settings.value("column1width", DefaultSettings::settings->autoDetectionTableColumnWidth).toInt());
	ui.tableWidget->setColumnWidth(2, settings.value("column2width", DefaultSettings::settings->autoDetectionTableColumnWidth).toInt());

	resize(settings.value("autoDetectionWindowWidth", DefaultSettings::settings->autoDetectionWindowWidth).toInt(),
	       settings.value("autoDetectionWindowHeight", DefaultSettings::settings->autoDetectionWindowHeight).toInt());
}

void AutoDetectionWindow::saveLayout()
{
	QSettings settings = QSettings();
	settings.setValue("column0width", ui.tableWidget->columnWidth(0));
	settings.setValue("column1width", ui.tableWidget->columnWidth(1));
	settings.setValue("column2width", ui.tableWidget->columnWidth(2));
	settings.setValue("autoDetectionWindowWidth", width());
	settings.setValue("autoDetectionWindowHeight", height());
}

void AutoDetectionWindow::saveTableContent()
{
	
}

void AutoDetectionWindow::onAddClick()
{
	ui.tableWidget->insertRow(ui.tableWidget->rowCount());
	ui.tableWidget->setCellWidget(0, 1, getTypeComboBox());
	ui.tableWidget->setCellWidget(0, 2,getConflictBehaviourComboBox());
}

void AutoDetectionWindow::onOkClick()
{
	saveLayout();
	saveTableContent();
	close();
}

void AutoDetectionWindow::onCancelClick()
{
	saveLayout();
	close();
}
