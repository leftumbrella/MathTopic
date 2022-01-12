#pragma once

#include <QWidget>
#include <QShowEvent>
#include "JsonMath.h"
#include "FunctionCore.h"
#include <qtmaterialfab.h>
#include <QLabel>
#include <qtmaterialdialog.h>
#include "ui_SubjectList.h"

class SubjectList : public QWidget
{
	Q_OBJECT

signals:
	void SubjectSelect(const QString& name);
	void SubjectNew();
	void GoHome();

public:
	SubjectList(QWidget *parent = Q_NULLPTR);
	~SubjectList();

private:
	void showEvent(QShowEvent* event) override;

private slots:
	void on_btn_add_clicked();

private:
	Ui::SubjectList ui;
	QtMaterialFloatingActionButton* _btn_home_ptr;
	QtMaterialFloatingActionButton* _btn_close_ptr;
	QtMaterialDialog* _close_dialog_ptr;
};
