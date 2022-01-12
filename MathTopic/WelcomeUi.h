#pragma once

#include <QWidget>
#include "ui_WelcomeUi.h"
#include <qtmaterialfab.h>
#include <QLabel>
#include <qtmaterialdialog.h>
#include "FunctionCore.h"

class WelcomeUi : public QWidget
{
	Q_OBJECT

public:
	WelcomeUi(QWidget *parent = Q_NULLPTR);
	~WelcomeUi();
signals:
	void GoTrain();
	void GoExam();
	void GoSetting();
	void GoData();
	void GoStatistics();
private slots:
	void ExitApp();
private:
	Ui::WelcomeUi ui;
	
	QtMaterialFloatingActionButton* _btn_setting_ptr;
	QtMaterialFloatingActionButton* _btn_statistics_ptr;
	QtMaterialFloatingActionButton* _btn_close_ptr;
	QtMaterialFloatingActionButton* _btn_data_ptr;
	QtMaterialDialog* _close_dialog_ptr;
	
};
