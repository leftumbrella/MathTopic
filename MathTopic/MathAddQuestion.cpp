#include "MathAddQuestion.h"

void MathAddQuestion::Initialize() {
	//ui.CB_operator->lineEdit()->setAlignment(Qt::AlignCenter);

	QRegExp rx("[0-9]+$");
	QRegExpValidator * validator = new QRegExpValidator(rx, this);
	ui.LE_left->setValidator(validator);
	ui.LE_right->setValidator(validator);
	ui.LE_answer->setValidator(validator);
	ui.btn_add_edit->setIconSize(QSize(50, 50));
	ui.btn_add_edit->setColor("#00b483");

	ui.btn_delete->setIcon(QIcon(":/Resources/image/delete.png"));
	ui.btn_delete->setColor("#89303f");
	ui.btn_delete->setIconSize(QSize(50, 50));

}

void MathAddQuestion::InsEdit() {
	QString left_str = ui.LE_left->text();
	QString right_str = ui.LE_right->text();

	if (left_str.isEmpty() || right_str.isEmpty()) {
		ui.btn_add_edit->setDisabled(true);
		return;
	}

	if (_is_auto_answer) {
		int answer_num = 0;
		int left_num = left_str.toInt();
		int right_num = right_str.toInt();
		int opt_index = ui.CB_operator->currentIndex();
		switch (opt_index)
		{
		case 0: answer_num = left_num + right_num;	break;
		case 1: answer_num = left_num - right_num;	break;
		case 2: answer_num = left_num * right_num;	break;
		case 3: answer_num = left_num / right_num;	break;
		}
		ui.LE_answer->setText(QString::number(answer_num));
		ui.btn_add_edit->setDisabled(false);
	}
	else {
		if (ui.LE_answer->text().isEmpty()) {
			ui.btn_add_edit->setDisabled(true);
		}
		else {
			ui.btn_add_edit->setDisabled(false);
		}
	}
}

MathAddQuestion::MathAddQuestion(QWidget *parent)
	: QWidget(parent),_is_auto_answer(false),_model(AddWait)
{
	ui.setupUi(this);
	ui.btn_add_edit->setDisabled(true);
	ui.btn_add_edit->setIcon(QIcon(":/Resources/image/add.png"));

	ui.btn_delete->hide();
	Initialize();
}

MathAddQuestion::MathAddQuestion(bool is_edit, QWidget* parent /*= Q_NULLPTR*/)
	:QWidget(parent),_is_auto_answer(false) {
	ui.setupUi(this);
	if (is_edit) {
		ui.btn_add_edit->setIcon(QIcon(":/Resources/image/edit.png"));
		
		_model = EditWait;
		ui.LE_left->setEnabled(false);
		ui.LE_right->setEnabled(false);
		ui.LE_answer->setEnabled(false);
		ui.CB_operator->setEditable(false);
	}else {
		ui.btn_add_edit->setIcon(QIcon(":/Resources/image/add.png"));
		_model = AddWait;
	}
	Initialize();
}

MathAddQuestion::MathAddQuestion(int left, int oper, int right, int answer, QWidget* parent /*= Q_NULLPTR*/)
	:QWidget(parent) {
	ui.setupUi(this);
	ui.btn_add_edit->setIcon(QIcon(":/Resources/image/edit.png"));
	ui.btn_delete->setIcon(QIcon(":/Resources/image/delete.png"));

	_model = EditWait;
	ui.LE_left->setEnabled(false);
	ui.LE_right->setEnabled(false);
	ui.LE_answer->setEnabled(false);
	ui.CB_operator->setEnabled(false);

	ui.LE_left->setText(QString::number(left));
	ui.LE_right->setText(QString::number(right));
	ui.LE_answer->setText(QString::number(answer));
	ui.CB_operator->setCurrentIndex(oper - 1);

	Initialize();
	ui.btn_add_edit->setColor("#f2c04d");
}

MathAddQuestion::~MathAddQuestion()
{
}

void MathAddQuestion::SetLeft(int left) {
	ui.LE_left->setText(QString::number(left));
}

void MathAddQuestion::SetOper(int oper) {
	ui.CB_operator->setCurrentIndex(oper - 1);
}

void MathAddQuestion::SetRight(int right) {
	ui.LE_right->setText(QString::number(right));
	int oper = ui.CB_operator->currentIndex() + 1;
	int answer_num = 0;
	switch (oper)
	{
	case 1: answer_num = ui.LE_left->text().toInt() + right;	break;
	case 2: answer_num = ui.LE_left->text().toInt() - right;	break;
	case 3: answer_num = ui.LE_left->text().toInt() * right;	break;
	case 4:
		if (right != 0) {
			answer_num = ui.LE_left->text().toInt() / right;
		}
		else {
			answer_num = 0;
		}

		break;
	}
	ui.LE_answer->setText(QString::number(answer_num));
	ui.btn_add_edit->setDisabled(false);
}

MathAddQuestion& MathAddQuestion::Clear() {
	ui.LE_left->setText("");
	ui.CB_operator->setCurrentIndex(0);
	ui.LE_right->setText("");
	ui.LE_answer->setText("");
	return *this;
}

bool MathAddQuestion::empty() {
	return ui.LE_left->text().isEmpty() || ui.CB_operator->currentIndex() == -1 ||
		ui.LE_right->text().isEmpty() || ui.LE_answer->text().isEmpty();
}

FORMULA MathAddQuestion::GetFormula() const {
	FORMULA formula;
	formula.left = ui.LE_left->text().toInt();
	formula.oper = ui.CB_operator->currentIndex()+1;
	formula.right = ui.LE_right->text().toInt();
	formula.answer = ui.LE_answer->text().toInt();
	return formula;
}

MathAddQuestion& MathAddQuestion::AutoAnswerSwitch(bool answer_switch) {
	_is_auto_answer = answer_switch;
	if (_is_auto_answer) {
		ui.LE_answer->setEnabled(false);
		if (!ui.LE_left->text().isEmpty() && !ui.LE_right->text().isEmpty()) {
			int answer_num = 0;
			int left_num = ui.LE_left->text().toInt();
			int right_num = ui.LE_right->text().toInt();
			int opt_index = ui.CB_operator->currentIndex();
			switch (opt_index)
			{
			case 0: answer_num = left_num + right_num;	break;
			case 1: answer_num = left_num - right_num;	break;
			case 2: answer_num = left_num * right_num;	break;
			case 3: answer_num = left_num / right_num;	break;
			}
			ui.LE_answer->setText(QString::number(answer_num));
			ui.btn_add_edit->setDisabled(false);
		}
	}
	else {
		ui.LE_answer->setEnabled(true);
	}
	return *this;
}

void MathAddQuestion::on_btn_add_edit_clicked() {
	switch (_model) {
	case AddWait: {
		int left_num = ui.LE_left->text().toInt();
		int right_num = ui.LE_right->text().toInt();
		int answer_num = ui.LE_answer->text().toInt();
		int opt_num = ui.CB_operator->currentIndex() + 1;
		emit QuestionAdd(FORMULA(left_num, opt_num, right_num, answer_num));
		ui.LE_left->setText("");
		ui.LE_right->setText("");
		ui.LE_answer->setText("");
		}
		break;
	case EditWait:
		ui.LE_left->setEnabled(true);
		ui.LE_right->setEnabled(true);
		ui.CB_operator->setEnabled(true);
		ui.btn_add_edit->setIcon(QIcon(":/Resources/image/finish.png"));
		ui.btn_add_edit->setColor("#00b483");
		_model = Editing;
		break;
	case Editing:
		ui.LE_left->setEnabled(false);
		ui.LE_right->setEnabled(false);
		ui.LE_answer->setEnabled(false);
		ui.CB_operator->setEnabled(false);
		ui.btn_add_edit->setIcon(QIcon(":/Resources/image/edit.png"));
		ui.btn_add_edit->setColor("#f2c04d");
		_model = EditWait;
		break;
	}
}

void MathAddQuestion::on_btn_delete_clicked() {
	emit QuestionDelete();
}

void MathAddQuestion::on_CB_operator_currentIndexChanged() {
	InsEdit();
}

void MathAddQuestion::on_LE_left_textEdited(const QString& text) {
	InsEdit();
}

void MathAddQuestion::on_LE_right_textEdited(const QString& text) {
	InsEdit();
}

void MathAddQuestion::on_LE_answer_textEdited(const QString& text) {
	InsEdit();
}
