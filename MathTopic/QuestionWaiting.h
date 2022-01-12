#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <vector>
#include "MathAddQuestion.h"
class QuestionWaiting : public QWidget {
	Q_OBJECT

public:
	QuestionWaiting(QWidget* parent = Q_NULLPTR);
	~QuestionWaiting();

	bool GetQuestions(std::vector<FORMULA>& formulas) const;
	void AutoAnswerSwitch(bool is_auto);
	void ClearAll();

private slots:
	void DelQuestion(MathAddQuestion* question_ptr);

public slots:
	void AddQuestion(const FORMULA& formula);


private:
	QVBoxLayout* _layout;

};
