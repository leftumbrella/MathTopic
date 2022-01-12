#pragma once

#include <QWidget>
#include <qtmaterialfab.h>
#include "FunctionCore.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QShowEvent>
#include "JsonMath.h"
#include <qtmaterialdialog.h>
#include "ui_SubjectChooser.h"

class SubjectChooser : public QWidget
{
	Q_OBJECT

signals:
	void GoHome();
	void GoSubject(const QString& sub_name);
	void GoSetting();
	void GoData();
	void GoStatistics();
public:
	SubjectChooser(QWidget *parent = Q_NULLPTR);
	~SubjectChooser();

private:
	void showEvent(QShowEvent* event) override;

private:
	Ui::SubjectChooser ui;
	QtMaterialFloatingActionButton* _btn_close_ptr;
	QtMaterialFloatingActionButton* _btn_setting_ptr;
	QtMaterialFloatingActionButton* _btn_statistics_ptr;
	QtMaterialFloatingActionButton* _btn_data_ptr;
	QtMaterialDialog* _close_dialog_ptr;
};
