#pragma once

#include <QWidget>
#include <QShowEvent>
#include "FunctionCore.h"
#include "ConfigCore.h"
#include <qtmaterialdialog.h>
#include "ui_QustionMathUi.h"

class QustionMathUi : public QWidget
{
	Q_OBJECT

signals:
	void Return();
	void StartMath();

public:
	QustionMathUi(QWidget *parent = Q_NULLPTR);
	~QustionMathUi();

private:
	void showEvent(QShowEvent* eve) override;

private slots:
	void on_btn_start_clicked();

private:
	Ui::QustionMathUi ui;
	QtMaterialDialog* _dialog_ptr;
};
