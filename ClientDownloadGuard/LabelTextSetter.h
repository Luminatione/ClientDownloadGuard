#pragma once
#include <QSharedPointer>
#include <QString>

class QLabel;

class LabelTextSetter
{
	QString text;
	QString prefix;
	QString suffix;

	QSharedPointer<QLabel> label;


public:

	LabelTextSetter(const QString& text, const QString& prefix, const QString& suffix,
		QLabel* label)
		: text(text),
		  prefix(prefix),
		  suffix(suffix),
		  label(label)
	{
	}
	void update();
	
	void setText(QString text);
	void setPrefix(QString text);
	void setSuffix(QString text);

	QString getText();
	QString getPrefix();
	QString getSuffix();
};

