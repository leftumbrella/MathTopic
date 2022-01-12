#pragma once

#include <QWidget>
#include <QRegExpValidator>
#include "ui_MathAddQuestion.h"
#include "MathTopicStructs.h"

class MathAddQuestion : public QWidget
{
	Q_OBJECT
private:
	enum Model {
		EditWait, AddWait ,Editing
	};

signals:
	void QuestionAdd( const FORMULA& formula);
	void QuestionDelete();
private:
	void Initialize();
	void InsEdit();
public:
	MathAddQuestion(QWidget *parent = Q_NULLPTR);
	MathAddQuestion(bool is_edit, QWidget* parent = Q_NULLPTR);
	MathAddQuestion(int left, int oper, int right, int answer, QWidget* parent = Q_NULLPTR);
	~MathAddQuestion();

	void SetLeft(int left);
	void SetOper(int oper);
	void SetRight(int right);

	MathAddQuestion& Clear();
	bool empty();

	FORMULA GetFormula() const;

	MathAddQuestion& AutoAnswerSwitch(bool answer_switch);

private slots:
	void on_btn_add_edit_clicked();
	void on_btn_delete_clicked();
	void on_CB_operator_currentIndexChanged();
	void on_LE_left_textEdited(const QString& text);
	void on_LE_right_textEdited(const QString& text);
	void on_LE_answer_textEdited(const QString& text);

private:
	Ui::MathAddQuestion ui;
	Model _model;
	bool _is_auto_answer;
};
