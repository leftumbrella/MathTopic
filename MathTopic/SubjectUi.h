#pragma once

#include <QWidget>
#include <QIcon>
#include <QtMaterialRaisedButton.h>
#include "FunctionCore.h"
#include "ui_SubjectUi.h"

class SubjectUi : public QWidget
{
	Q_OBJECT

signals:
	void Return();
	void SelectSubject(int);

public:
	SubjectUi(QWidget *parent = Q_NULLPTR);
	~SubjectUi();

private:
	Ui::SubjectUi ui;
};
