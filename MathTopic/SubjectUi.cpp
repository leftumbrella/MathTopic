#include "SubjectUi.h"

SubjectUi::SubjectUi(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.btn_chinese->setIcon(QIcon(":/MathTopic/Chinese.png"));
	ui.btn_chinese->setBackgroundColor("#a381ba");
	ui.btn_math->setIcon(QIcon(":/MathTopic/Math.png"));
	ui.btn_math->setBackgroundColor("#a381ba");
	ui.btn_english->setIcon(QIcon(":/MathTopic/English.png"));
	ui.btn_english->setBackgroundColor("#a381ba");

	connect(ui.btn_chinese, &QtMaterialRaisedButton::clicked, this, [=](){
		QPlaySound(3);
		emit SelectSubject(1);
		});
	connect(ui.btn_math, &QtMaterialRaisedButton::clicked, this, [=]() {
		QPlaySound(3);
		emit SelectSubject(2);
		});
	connect(ui.btn_english, &QtMaterialRaisedButton::clicked, this, [=]() {
		QPlaySound(3);
		emit SelectSubject(3);
		});

	ui.btn_return->setIcon(QIcon(":/MathTopic/return.png"));
	ui.btn_return->setBackgroundColor("#9bae86");
	connect(ui.btn_return, &QtMaterialRaisedButton::clicked, this, &SubjectUi::Return);
	connect(ui.btn_return, &QtMaterialRaisedButton::clicked, this, [=]() {
		QPlaySound(3);
		});
}

SubjectUi::~SubjectUi()
{
}
