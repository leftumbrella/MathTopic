#pragma once

#include <QWidget>
#include <Json/json.hpp>
#include <fstream>
#include <iomanip>
#include <sstream>
#include "SubjectOne.h"
#include <QVBoxLayout>

class SubjectsUi : public QWidget
{
	Q_OBJECT

signals:
	void SubjectSelect(const QString& subject_name);

private slots:
	void DelSubject(SubjectOne* question_ptr);

public slots:
	void AddSubject(const QString& name);

public:
	SubjectsUi(QWidget *parent);
	~SubjectsUi();
	void ClearAll();
	void NoDelete();
private:
	QVBoxLayout* _layout;
	bool _have_delete;
};
