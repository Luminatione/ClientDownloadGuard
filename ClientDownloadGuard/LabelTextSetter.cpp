#include <QLabel>

#include "LabelTextSetter.h"


void LabelTextSetter::update()
{
	label.get()->setText(prefix + text + suffix);
}

void LabelTextSetter::setText(QString text)
{
	this->text = text;
	update();
}

void LabelTextSetter::setPrefix(QString text)
{
	this->prefix = text;
	update();
}

void LabelTextSetter::setSuffix(QString text)
{
	this->suffix= text;
	update();
}

QString LabelTextSetter::getText()
{
	return text;
}

QString LabelTextSetter::getPrefix()
{
	return prefix;
}

QString LabelTextSetter::getSuffix()
{
	return suffix;
}
