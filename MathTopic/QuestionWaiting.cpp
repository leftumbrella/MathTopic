#include "QuestionWaiting.h"

QuestionWaiting::QuestionWaiting(QWidget *parent)
	: QWidget(parent), _layout(new QVBoxLayout)
{
	setLayout(_layout);
	_layout->setMargin(0);
	_layout->setSpacing(0);
}

QuestionWaiting::~QuestionWaiting()
{
	delete _layout;
}

bool QuestionWaiting::GetQuestions(std::vector<FORMULA>& formulas) const {
	QList<MathAddQuestion*> questions = findChildren<MathAddQuestion*>();
	for (QList<MathAddQuestion*>::const_iterator itr = questions.cbegin(); itr != questions.cend(); ++itr) {
		formulas.push_back((*itr)->GetFormula());
	}
	return !formulas.empty();
}

void QuestionWaiting::AutoAnswerSwitch(bool is_auto) {
	QList<MathAddQuestion*> questions = findChildren<MathAddQuestion*>();
	for (QList<MathAddQuestion*>::const_iterator itr = questions.cbegin(); itr != questions.cend(); ++itr) {
		(*itr)->AutoAnswerSwitch(is_auto);
	}
}

void QuestionWaiting::ClearAll() {
	QList<MathAddQuestion*> questions = findChildren<MathAddQuestion*>();
	for (QList<MathAddQuestion*>::const_iterator itr = questions.cbegin(); itr != questions.cend(); ++itr) {
		this->setFixedHeight(height() - (*itr)->height());
		_layout->removeWidget((*itr));
		(*itr)->hide();
		delete (*itr);
	}
}

void QuestionWaiting::DelQuestion(MathAddQuestion* question_ptr) {
	this->setFixedHeight(height() - question_ptr->height());
	_layout->removeWidget(question_ptr);
	question_ptr->hide();
	delete question_ptr;
}

void QuestionWaiting::AddQuestion(int left, int opt, int right, int answer) {
	MathAddQuestion* math_question = new MathAddQuestion(left, opt, right, answer, this);
	connect(math_question, &MathAddQuestion::QuestionDelete, this, [=]() {
		DelQuestion(math_question);
		});
	_layout->addWidget(math_question);
	this->setFixedHeight(height() + math_question->height());
}
