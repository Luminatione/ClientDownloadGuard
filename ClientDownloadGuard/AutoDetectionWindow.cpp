#include "AutoDetectionWindow.h"
#include "QtMacros.h"
#include "DefaultSettings.h"

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
	BUTTON_CLICK_TO_THIS_CONNECTION(ui.removeButton, onRemoveClick());
	BUTTON_CLICK_TO_THIS_CONNECTION(ui.cancelButton, onCancelClick());
}

int AutoDetectionWindow::getCurrentIndexOfCellWidgetAsComboBox(int row, int column)
{
	return dynamic_cast<QComboBox*>(ui.tableWidget->cellWidget(row, column))->currentIndex();
}

void AutoDetectionWindow::closeEvent(QCloseEvent* event)
{
	emit destroyed();
}

QComboBox* AutoDetectionWindow::getComboBoxWithItems(QStringList& items)
{
	QComboBox* comboBox = new QComboBox();
	comboBox->addItems(items);
	return comboBox;
}

QComboBox* AutoDetectionWindow::getTypeComboBox()
{
	QStringList options{ "Free", "Downloading", "Ask not to download", "None" };
	return getComboBoxWithItems(options);
}

QComboBox* AutoDetectionWindow::getConflictBehaviourComboBox()
{
	QStringList options{ "Ignore", "Notify me", "Abandon" };
	return getComboBoxWithItems(options);
}

void AutoDetectionWindow::setIndexAtColumnAsComboBox(int column, int value)
{
	dynamic_cast<QComboBox*>(ui.tableWidget->cellWidget(ui.tableWidget->rowCount() - 1, column))->setCurrentIndex(value);
}

void AutoDetectionWindow::readRecord()
{
	AutoDetectionRecord autoDetectionRecord = autoDetectionIO.getNextRecord();
	ui.tableWidget->item(ui.tableWidget->rowCount() - 1, 0)->setText(autoDetectionRecord.windowName);
	setIndexAtColumnAsComboBox(1, autoDetectionRecord.type);
	setIndexAtColumnAsComboBox(2, autoDetectionRecord.conflictBehaviour);
}

void AutoDetectionWindow::loadTableContent()
{
	autoDetectionIO.resetFileCursor();
	while (!autoDetectionIO.atEnd())
	{
		onAddClick();
		readRecord();
	}
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
	autoDetectionIO.truncate();
	autoDetectionIO.resetFileCursor();
	for (int i = 0; i < ui.tableWidget->rowCount(); ++i)
	{
		QString windowName = ui.tableWidget->item(i, 0)->text();
		autoDetectionIO.saveRecord(AutoDetectionRecord{ windowName, getCurrentIndexOfCellWidgetAsComboBox(i, 1), getCurrentIndexOfCellWidgetAsComboBox(i, 2) });
	}
}

void AutoDetectionWindow::onAddClick()
{
	ui.tableWidget->insertRow(ui.tableWidget->rowCount());
	ui.tableWidget->setCellWidget(ui.tableWidget->rowCount() - 1, 1, getTypeComboBox());
	ui.tableWidget->setCellWidget(ui.tableWidget->rowCount() - 1, 2, getConflictBehaviourComboBox());
	ui.tableWidget->setItem(ui.tableWidget->rowCount() - 1, 0, new QTableWidgetItem());
	ui.tableWidget->setItem(ui.tableWidget->rowCount() - 1, 1, new QTableWidgetItem());
	ui.tableWidget->setItem(ui.tableWidget->rowCount() - 1, 2, new QTableWidgetItem());
}

void AutoDetectionWindow::onOkClick()
{
	saveLayout();
	saveTableContent();
	autoDetectionIO.closeFile();
	close();
}

void AutoDetectionWindow::onCancelClick()
{
	saveLayout();
	autoDetectionIO.closeFile();
	close();
}

void AutoDetectionWindow::onRemoveClick()
{
	ui.tableWidget->removeRow(ui.tableWidget->currentRow());
}
