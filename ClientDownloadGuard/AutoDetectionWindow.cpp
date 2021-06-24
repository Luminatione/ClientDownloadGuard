#include "AutoDetectionWindow.h"
#include "QtMacros.h"
#include "DefaultSettings.h"

#include <QTreeWidget>
#include <QComboBox>
#include <QSettings>
#include <QFile>
#include <QMessageBox>

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
	QStringList options{ "Free", "Downloading", "Ask not to download" };
	return getComboBoxWithItems(options);
}

QComboBox* AutoDetectionWindow::getConflictBehaviourComboBox()
{
	QStringList options{ "Ignore", "Notify me", "Abandon" };
	return getComboBoxWithItems(options);
}

void AutoDetectionWindow::setValueAtColumnAsComboBox(int column, int value)
{
	dynamic_cast<QComboBox*>(ui.tableWidget->cellWidget(ui.tableWidget->rowCount() - 1, column))->setCurrentIndex(value);
}

void AutoDetectionWindow::readRecord(QDataStream& stream)
{
	onAddClick();
	ui.tableWidget->item(ui.tableWidget->rowCount() - 1, 0)->read(stream);
	int temp = 0;
	stream >> temp;
	setValueAtColumnAsComboBox(1, temp);
	stream >> temp;
	setValueAtColumnAsComboBox(2, temp);
}

void AutoDetectionWindow::loadTableContent()
{
	QFile file = QFile(QCoreApplication::applicationDirPath() + "/auto detection.dat");
	QDataStream stream = QDataStream(&file);
	if (!file.open(QIODevice::ReadOnly) && file.exists())
	{
		QMessageBox::critical(this, "Error", "Failed to Load File");
		return;
	}
	while (!stream.atEnd())
	{
		readRecord(stream);
	}
	file.flush();
	file.close();
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
	QFile file = QFile(QCoreApplication::applicationDirPath() + "/auto detection.dat");
	QDataStream stream = QDataStream(&file);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
	{
		QMessageBox::critical(this, "Error", "Failed to save Changes");
		return;
	}
	for (int i = 0; i < ui.tableWidget->rowCount(); ++i)
	{
		ui.tableWidget->item(i, 0)->write(stream);
		stream << dynamic_cast<QComboBox*>(ui.tableWidget->cellWidget(i, 1))->currentIndex();
		stream << dynamic_cast<QComboBox*>(ui.tableWidget->cellWidget(i, 2))->currentIndex();
	}
	file.flush();
	file.close();
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
	close();
}

void AutoDetectionWindow::onCancelClick()
{
	saveLayout();
	close();
}
