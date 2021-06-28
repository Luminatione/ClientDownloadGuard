#include "ScheduleWindow.h"
#include "QtMacros.h"

#include <QMessageBox>


ScheduleWindow::ScheduleWindow(QWidget* parent) : QMainWindow(parent)
{
	ui.setupUi(this);
	if (!file.open(QIODeviceBase::ReadWrite) && file.exists())
	{
		QMessageBox::critical(nullptr, "Error", "Failed to open file");
	}
	setupConnections();
	loadRecords();
	displayRecords();
}

void ScheduleWindow::setupConnections()
{
	BUTTON_CLICK_TO_THIS_CONNECTION(ui.addButton, onAddClick());
	BUTTON_CLICK_TO_THIS_CONNECTION(ui.removeButton, onRemoveClick());
	BUTTON_CLICK_TO_THIS_CONNECTION(ui.closeButton, onCloseClick());
	BUTTON_CLICK_TO_THIS_CONNECTION(ui.confirmButton, onConfirmClick());
	bool a = connect(ui.listWidget, &QListWidget::itemSelectionChanged, this, &ScheduleWindow::onSelectionChanged);
}

void ScheduleWindow::loadRecords()
{
	while (!dataStream.atEnd())
	{
		ScheduleRecord record;
		dataStream >> record;
		records.push_back(record);
	}
}

void ScheduleWindow::displayRecords()
{
	for (auto& record : records)
	{
		addItemToList(record.name);
	}
}

void ScheduleWindow::addItemToList(QString& name)
{
	ui.listWidget->addItem(name);
	QListWidgetItem* item = ui.listWidget->item(ui.listWidget->count() - 1);
	item->setFlags(item->flags() | Qt::ItemIsEditable);
	ui.listWidget->editItem(item);
	records.push_back(ScheduleRecord());
}

void ScheduleWindow::saveRecords()
{
	for (auto& record : records)
	{
		dataStream << record;
	}
}

void ScheduleWindow::truncateFile()
{
	closeFile();
	file.open(QIODeviceBase::ReadWrite | QIODeviceBase::Truncate);
}

void ScheduleWindow::closeFile()
{
	file.flush();
	file.close();
}

ScheduleWindow::~ScheduleWindow()
{
	saveRecords();
	closeFile();
}

void ScheduleWindow::onAddClick()
{
	QString name = "New item";
	addItemToList(name);
}

void ScheduleWindow::onCloseClick()
{
	close();
}

void ScheduleWindow::onRemoveClick()
{
	qDeleteAll(ui.listWidget->selectedItems());
}

void ScheduleWindow::onSelectionChanged()
{
	int selectedIndex = ui.listWidget->currentRow();
	ScheduleRecord* record = &records[selectedIndex];
	ui.nameLineEdit->setText(record->name);
	ui.enabledCheckBox->setChecked(record->enabled);
	ui.behaviourComboBox->setCurrentIndex(record->behaviour);
	ui.beginTimeEdit->setTime(record->begin);
	ui.endTimeEdit->setTime(record->end);
	ui.typeComboBox->setCurrentIndex(record->type);
	ui.onConflictBehaviourComboBox->setCurrentIndex(record->onConflictBehaviour);
	ui.removeOnEndCheckBox->setChecked(record->removeOnEnd);
}

void ScheduleWindow::onConfirmClick()
{
	int selectedIndex = ui.listWidget->currentRow();
	ScheduleRecord* record = &records[selectedIndex];
	record->name = ui.nameLineEdit->text();
	record->enabled = ui.enabledCheckBox->isChecked();
	record->behaviour = ui.behaviourComboBox->currentIndex();
	record->begin = ui.beginTimeEdit->time();
	record->end = ui.endTimeEdit->time();
	record->type = ui.typeComboBox->currentIndex();
	record->onConflictBehaviour = ui.onConflictBehaviourComboBox->currentIndex();
	record->removeOnEnd = ui.removeOnEndCheckBox->isChecked();
}
