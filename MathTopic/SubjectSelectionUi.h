#pragma once

#include <QWidget>
#include <qtmaterialtabs_internal.h>

#include "ui_SubjectSelectionUi.h"

class SubjectSelectionUi : public QWidget
{
	Q_OBJECT

signals:
	void GoWelcome();
	void Start(int type);

private slots:
	void GoQuestion(int question_type);
private:
	void showEvent(QShowEvent* event) override;

public:
	SubjectSelectionUi(QWidget *parent = Q_NULLPTR);
	~SubjectSelectionUi();
	

private:
	Ui::SubjectSelectionUi ui;

};
