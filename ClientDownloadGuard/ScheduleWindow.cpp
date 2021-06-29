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
	setLayoutWidgetsEnabledState(false);
	daysCheckBoxes[0] = ui.mondayCheckBox;
	daysCheckBoxes[1] = ui.tuesdayCheckBox;
	daysCheckBoxes[2] = ui.wednesdayCheckBox;
	daysCheckBoxes[3] = ui.thursdayCheckBox;
	daysCheckBoxes[4] = ui.fridayCheckBox;
	daysCheckBoxes[5] = ui.saturdayCheckBox;
	daysCheckBoxes[6] = ui.sundayCheckBox;

}

void ScheduleWindow::setupConnections()
{
	BUTTON_CLICK_TO_THIS_CONNECTION(ui.addButton, onAddClick());
	BUTTON_CLICK_TO_THIS_CONNECTION(ui.removeButton, onRemoveClick());
	BUTTON_CLICK_TO_THIS_CONNECTION(ui.closeButton, onCloseClick());
	BUTTON_CLICK_TO_THIS_CONNECTION(ui.confirmButton, onConfirmClick());
	connect(ui.listWidget, &QListWidget::itemSelectionChanged, this, &ScheduleWindow::onSelectionChanged);
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
	QListWidgetItem* lastItem = ui.listWidget->item(ui.listWidget->count() - 1);
	lastItem->setFlags(lastItem->flags() | Qt::ItemIsEditable);
}

void ScheduleWindow::saveRecords()
{
	truncateFile();
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

void ScheduleWindow::setLayoutWidgetsEnabledState(bool state, QLayout* layout)
{
	QLayout* currentLayout = layout ? layout : ui.verticalLayout;
	for (int i = 0; i < currentLayout->count(); i++)
	{
		QWidget* widget = currentLayout->itemAt(i)->widget();
		QLayout* underlyingLayout = currentLayout->itemAt(i)->layout();
		if (widget)
		{
			widget->setEnabled(state);
		}
		if (underlyingLayout)
		{
			setLayoutWidgetsEnabledState(state, underlyingLayout);
		}
	}
}

void ScheduleWindow::closeEvent(QCloseEvent* event)
{
	saveRecords();
	closeFile();
}

int ScheduleWindow::daysToNumber()
{
	int result = 0;
	for (auto* checkBox : daysCheckBoxes)
	{
		result += checkBox->isChecked();
		result <<= 1;
	}
	result >>= 1;
	return result;
}

void ScheduleWindow::setDaysFromNumber(int number)
{
	int mask = 0b1000000;
	for (auto* checkBox : daysCheckBoxes)
	{
		checkBox->setChecked(number & mask);
		mask >>= 1;
	}
}

ScheduleWindow::~ScheduleWindow()
{
}

void ScheduleWindow::onAddClick()
{
	QString name = "New item";
	addItemToList(name);
	ScheduleRecord record;
	record.name = name;
	records.push_back(record);
	ui.listWidget->editItem(ui.listWidget->item(ui.listWidget->count() - 1));
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
	if (selectedIndex == -1)
	{
		setLayoutWidgetsEnabledState(false);
		return;
	}
	setLayoutWidgetsEnabledState(true);
	ScheduleRecord* record = &records[selectedIndex];
	ui.nameLineEdit->setText(record->name);
	ui.enabledCheckBox->setChecked(record->enabled);
	ui.behaviourComboBox->setCurrentIndex(record->behaviour);
	ui.beginTimeEdit->setTime(record->begin);
	ui.endTimeEdit->setTime(record->end);
	setDaysFromNumber(record->days);
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
	record->days = daysToNumber();
	record->type = ui.typeComboBox->currentIndex();
	record->onConflictBehaviour = ui.onConflictBehaviourComboBox->currentIndex();
	record->removeOnEnd = ui.removeOnEndCheckBox->isChecked();
}
