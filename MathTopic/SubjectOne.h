#pragma once

#include <QWidget>
#include <QIcon>
#include "ui_SubjectOne.h"

class SubjectOne : public QWidget
{
	Q_OBJECT

signals:
	void SubjectSelect();
	void SubjectDelete();

public:
	SubjectOne(const QString& name , QWidget *parent = Q_NULLPTR ,bool have_delete = true);
	~SubjectOne();
	QString& Name();

private slots:
	void on_btn_subject_clicked();
	void on_btn_delete_clicked();

private:
	Ui::SubjectOne ui;

	QString _name;
};
