#pragma once

#include <QWidget>
#include <qtmaterialfab.h>
#include <QShowEvent>
#include "ConfigCore.h"
#include "FunctionCore.h"
#include "ui_StatisticsUi.h"

class StatisticsUi : public QWidget
{
	Q_OBJECT

signals:
	void GoWelcome();

public:
	StatisticsUi(QWidget *parent = Q_NULLPTR);
	~StatisticsUi();

private:
	void showEvent(QShowEvent* event) override;

private:
	Ui::StatisticsUi ui;
	QtMaterialFloatingActionButton* _btn_home_ptr;
};
