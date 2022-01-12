#pragma once

#include <QWidget>
#include "FunctionCore.h"
#include <qtmaterialfab.h>
#include <QLabel>
#include <qtmaterialdialog.h>
#include "ui_EndUi.h"

class EndUi : public QWidget
{
	Q_OBJECT

signals:
	void GoHome();
	void ReTry(const QString& sub_name);

public slots:
	void ChangeOver(const QString& subname ,int ok_num, int error_num, std::time_t time);

public:
	EndUi(QWidget *parent = Q_NULLPTR);
	~EndUi();

private:
	Ui::EndUi ui;
	QtMaterialFloatingActionButton* _btn_close_ptr;
	QtMaterialDialog* _close_dialog_ptr;

	QString _sub_name;
};
