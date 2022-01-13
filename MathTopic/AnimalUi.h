#pragma once

#include <QWidget>
#include <QIcon>
#include <QLabel>
#include "ui_AnimalUi.h"

class AnimalUi : public QWidget
{
	Q_OBJECT

public:
	AnimalUi(QWidget *parent = Q_NULLPTR);
	~AnimalUi();

	bool setAnimal(int left, int oper, int right);

private:
	Ui::AnimalUi ui;
	QString _2R_row_style;
	QString _2L_row_style;
	QString _2R_rbt_style;
	QString _2L_rbt_style;
};
