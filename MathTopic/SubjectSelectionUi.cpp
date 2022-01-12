#include "SubjectSelectionUi.h"


void SubjectSelectionUi::GoQuestion(int question_type) {
	if (question_type == 2) {
		ui.stackedWidget->setCurrentWidget(ui.PG_QuestionMath);
	}
}

void SubjectSelectionUi::showEvent(QShowEvent* event) {
	QWidget::showEvent(event);
	ui.stackedWidget->setCurrentWidget(ui.PG_Subject);
}

SubjectSelectionUi::SubjectSelectionUi(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	connect(ui.PG_Subject, &SubjectUi::Return, this, &SubjectSelectionUi::GoWelcome);
	connect(ui.PG_Subject, &SubjectUi::SelectSubject, this, &SubjectSelectionUi::GoQuestion);
	connect(ui.PG_QuestionMath, &QustionMathUi::Return, this, [=]() {
		ui.stackedWidget->setCurrentWidget(ui.PG_Subject);
		});
	connect(ui.PG_QuestionMath, &QustionMathUi::StartMath, this, [=]() {
		emit Start(2);
		});
}

SubjectSelectionUi::~SubjectSelectionUi(){

}