#include "MathTopicConf.h"
extern std::string MathSubjectsPath;
MathTopicConf::MathTopicConf(QWidget *parent)
	: QWidget(parent)
	, _btn_close_ptr(new QtMaterialFloatingActionButton(QIcon(":/MathTopic/close.png"), this))
	, _btn_home_ptr(new QtMaterialFloatingActionButton(QIcon(":/MathTopic/home.png"), this))
	, _close_dialog_ptr(new QtMaterialDialog(this))
	, _info_dialog_ptr(new QtMaterialDialog(this))
	, _override_ptr(new QtMaterialDialog(this))
	,_left_num(0),_oper_num(1),_have_oper(false),_right_num(0), _is_editing(false)
{
	ui.setupUi(this);

	ui.btn_finish->setBackgroundColor("#168570");
	ui.btn_select->setBackgroundColor("#168570");

	_btn_home_ptr->setCorner(Qt::TopLeftCorner);
	_btn_home_ptr->setBackgroundColor("#168570");

	_btn_home_ptr->setToolTip(QStringLiteral("主页"));
	_btn_close_ptr->setToolTip(QStringLiteral("关闭软件"));

	connect(_btn_home_ptr, &QtMaterialFloatingActionButton::clicked, this, [=]() {
		QPlaySound(3);
		emit GoHome();
		});

	connect(ui.WG_adder, &MathAddQuestion::QuestionAdd, ui.WG_waitting, &QuestionWaiting::AddQuestion);

	ui.CB_fast->setToolTip(QStringLiteral("进入快速模式后，答案始终为自动计算\n输入数字及“+、-、*、/”符号系统自动保存\n完成后按下“Enter键”将其添加到列表中\n您也可以按下“Delete”键来删除输入的缓存？\n例如:输入 “1” “+” “1” “Enter”"));

	
	ui.btn_select->setIcon(QIcon(":/MathTopic/select_other.png"));
	ui.btn_finish->setIcon(QIcon(":/MathTopic/btn_over.png"));

	connect(ui.btn_select, &QtMaterialRaisedButton::clicked, this, [=]() {
		QPlaySound(3);
		_is_editing = false;
		emit GoSelectSubject();
		});

	_btn_close_ptr->setCorner(Qt::TopRightCorner);
	_btn_close_ptr->setBackgroundColor("#973444");

	{// 设置对话框
		QVBoxLayout* dialogLayout = new QVBoxLayout;
		_close_dialog_ptr->setWindowLayout(dialogLayout);

		QWidget* WG_dialog = new QWidget(_close_dialog_ptr);
		QVBoxLayout* LY_dialog = new QVBoxLayout;
		WG_dialog->setLayout(LY_dialog);
		QtMaterialFlatButton* btn_ok = new QtMaterialFlatButton(QStringLiteral("休息一下"));
		QtMaterialFlatButton* btn_cancel = new QtMaterialFlatButton(QStringLiteral("我点错了"));

		connect(btn_ok, &QtMaterialFlatButton::clicked, this, []() {
			QApplication::exit(0);
			});
		connect(btn_cancel, &QtMaterialFlatButton::clicked, _close_dialog_ptr, &QtMaterialDialog::hideDialog);
		connect(btn_cancel, &QtMaterialFlatButton::clicked, this, [=]() {
			QPlaySound(3);
			});

		QLabel* label_ptr = new QLabel(WG_dialog);
		QFont font;
		QStringList family;
		family << QStringLiteral("Consolas") << QStringLiteral("楷体");
		font.setFamilies(family);
		font.setPointSize(20);
		label_ptr->setFont(font);
		font.setPointSize(15);
		font.setBold(true);
		btn_ok->setFont(font);
		btn_cancel->setFont(font);

		QWidget* WG_dia_btns = new QWidget(_close_dialog_ptr);
		QHBoxLayout* LY_dia_btns = new QHBoxLayout;
		WG_dia_btns->setLayout(LY_dia_btns);
		LY_dia_btns->addWidget(btn_ok);
		LY_dia_btns->addWidget(btn_cancel);

		label_ptr->setText(QStringLiteral("要暂时停止练习了嘛？"));
		LY_dialog->addWidget(label_ptr);
		LY_dialog->addSpacing(1);
		LY_dialog->addWidget(WG_dia_btns);
		LY_dialog->setAlignment(label_ptr, Qt::AlignTop | Qt::AlignCenter);


		dialogLayout->addWidget(WG_dialog);

		connect(_btn_close_ptr, &QtMaterialFloatingActionButton::clicked, _close_dialog_ptr, &QtMaterialDialog::showDialog);
		connect(_btn_close_ptr, &QtMaterialFloatingActionButton::clicked, this, [=]() {
			QPlaySound(4);
			});
	}

	{// 设置对话框
		QVBoxLayout* dialogLayout = new QVBoxLayout;
		_info_dialog_ptr->setWindowLayout(dialogLayout);

		QWidget* WG_dialog = new QWidget(_close_dialog_ptr);
		QVBoxLayout* LY_dialog = new QVBoxLayout;
		WG_dialog->setLayout(LY_dialog);
		QtMaterialFlatButton* btn_ok = new QtMaterialFlatButton(QStringLiteral("我知道啦"));

		connect(btn_ok, &QtMaterialFlatButton::clicked, this, [=]() {
			QPlaySound(3);
			_info_dialog_ptr->hide();
			});

		QLabel* label_ptr = new QLabel(WG_dialog);
		QFont font;
		QStringList family;
		family << QStringLiteral("Consolas") << QStringLiteral("楷体");
		font.setFamilies(family);
		font.setPointSize(20);
		label_ptr->setFont(font);
		font.setPointSize(15);
		font.setBold(true);
		btn_ok->setFont(font);

		QWidget* WG_dia_btns = new QWidget(_close_dialog_ptr);
		QHBoxLayout* LY_dia_btns = new QHBoxLayout;
		WG_dia_btns->setLayout(LY_dia_btns);
		LY_dia_btns->addWidget(btn_ok);
		label_ptr->setAlignment(Qt::AlignCenter);
		label_ptr->setText(QStringLiteral("进入快速模式后，答案始终为自动计算\n输入数字及“+、-、*、/”符号系统自动保存\n完成后按下“Enter键”将其添加到列表中\n您也可以按下“Delete”键来删除输入的缓存？\n例如:输入 “1” “+” “1” “Enter”"));
		LY_dialog->addWidget(label_ptr);
		LY_dialog->addSpacing(1);
		LY_dialog->addWidget(WG_dia_btns);
		LY_dialog->setAlignment(label_ptr, Qt::AlignTop | Qt::AlignCenter);


		dialogLayout->addWidget(WG_dialog);
	}
	{// 设置对话框
		QVBoxLayout* dialogLayout = new QVBoxLayout;
		_override_ptr->setWindowLayout(dialogLayout);

		QWidget* WG_dialog = new QWidget(_close_dialog_ptr);
		QVBoxLayout* LY_dialog = new QVBoxLayout;
		WG_dialog->setLayout(LY_dialog);
		QtMaterialFlatButton* btn_ok = new QtMaterialFlatButton(QStringLiteral("我要覆盖"));
		QtMaterialFlatButton* btn_cancel = new QtMaterialFlatButton(QStringLiteral("我再看看"));

		connect(btn_ok, &QtMaterialFlatButton::clicked, this, [=]() {
			QPlaySound(3);
			_override_ptr->hideDialog(); 
			if (SaveFormulas(true)==0) {
				_is_editing = false;
				emit GoSelectSubject();
			}
			});
		connect(btn_cancel, &QtMaterialFlatButton::clicked, this, [=]() {
			QPlaySound(3);
			_override_ptr->hideDialog();
			});

		QLabel* label_ptr = new QLabel(WG_dialog);
		QFont font;
		QStringList family;
		family << QStringLiteral("Consolas") << QStringLiteral("楷体");
		font.setFamilies(family);
		font.setPointSize(20);
		label_ptr->setFont(font);
		font.setPointSize(15);
		font.setBold(true);
		btn_ok->setFont(font);
		btn_cancel->setFont(font);

		QWidget* WG_dia_btns = new QWidget(_close_dialog_ptr);
		QHBoxLayout* LY_dia_btns = new QHBoxLayout;
		WG_dia_btns->setLayout(LY_dia_btns);
		LY_dia_btns->addWidget(btn_ok);
		LY_dia_btns->addWidget(btn_cancel);
		label_ptr->setAlignment(Qt::AlignCenter);
		label_ptr->setText(QStringLiteral("当前有相同名称的科目，要把它覆盖掉嘛？"));
		LY_dialog->addWidget(label_ptr);
		LY_dialog->addSpacing(1);
		LY_dialog->addWidget(WG_dia_btns);
		LY_dialog->setAlignment(label_ptr, Qt::AlignTop | Qt::AlignCenter);


		dialogLayout->addWidget(WG_dialog);
	}
}

MathTopicConf::~MathTopicConf()
{
}

bool MathTopicConf::load(const QString& sub_name) {
	_is_editing = true;
	std::ifstream file;
	file.open(MathSubjectsPath, std::ios::in);
	if (!file.is_open()) {
		return false;
	}
	nlohmann::json js;
	file >> js;
	file.close();
	nlohmann::json::const_iterator find_base = js.find("MathSubjects");
	if (find_base != js.cend()) {
		nlohmann::json::const_iterator find = find_base->find(sub_name.toStdString());
		if (find != find_base->cend() && !find.value().empty()) {
			ui.LE_name->setText(QString::fromStdString(find.key()));
			nlohmann::json::const_iterator itr;
			for (itr = find.value().cbegin(); itr != find.value().cend(); ++itr) {
				std::string formula_str = itr.value();
				if (!formula_str.empty()) {
					AddFormula(formula_str);
				}
			}
		}
	}
	return true;
}

void MathTopicConf::showEvent(QShowEvent* event) {
	QWidget::showEvent(event);
	ui.WG_waitting->ClearAll();
	ui.LE_name->setText(QStringLiteral("未命名课题"));
}

void MathTopicConf::keyPressEvent(QKeyEvent* event) {
	switch (event->key()) {
	case Qt::Key_Delete:	ClearPush();	break;
		case Qt::Key_Enter:	OverPush();	break;
		case Qt::Key_0: Push(0);	break;
		case Qt::Key_1: Push(1);	break;
		case Qt::Key_2: Push(2);	break;
		case Qt::Key_3: Push(3);	break;
		case Qt::Key_4: Push(4);	break;
		case Qt::Key_5: Push(5);	break;
		case Qt::Key_6: Push(6);	break;
		case Qt::Key_7: Push(7);	break;
		case Qt::Key_8: Push(8);	break;
		case Qt::Key_9: Push(9);	break;
		case Qt::Key_Plus:	Push(10);	break;
		case Qt::Key_Minus: Push(11);	break;
		case Qt::Key_Asterisk: Push(12);	break;
		case Qt::Key_Slash: Push(13);	break;
	}

	QWidget::keyPressEvent(event);
}

void MathTopicConf::Push(int push_what) {
	
	if (!_have_oper) {
		if (push_what > 9) {
			_have_oper = true;
			_oper_num = push_what - 9;
			ui.WG_adder->SetOper(_oper_num);
			return;
		}
		if (_left_num == 0) {
			_left_num = push_what;
		}else {
			_left_num = _left_num * 10 + push_what;
		}
		ui.WG_adder->SetLeft(_left_num);
	}
	else {
		if (push_what > 9) {
			return;
		}
		if (_right_num == 0) {
			_right_num = push_what;
		}
		else {
			_right_num = _right_num * 10 + push_what;
		}
		ui.WG_adder->SetRight(_right_num);
	}

}

void MathTopicConf::OverPush() {
	if (!ui.WG_adder->empty()) {
		FORMULA tmp = ui.WG_adder->GetFormula();
		ui.WG_waitting->AddQuestion(tmp.left, tmp.oper, tmp.right, tmp.answer);
		ClearPush();
	}
}

void MathTopicConf::ClearPush() {
	_left_num = _right_num = _oper_num = 0;
	_have_oper = false;
	ui.WG_adder->Clear();
}

void MathTopicConf::on_btn_finish_clicked() {
	int res = SaveFormulas();
	switch (res)
	{
		case 0:
			_is_editing = false;
			emit GoSelectSubject();
			break;
	}

	
}

void MathTopicConf::on_CB_fast_toggled(bool) {
	if (ui.CB_fast->isChecked()) {
		ui.CB_auto_answer->setChecked(true);
		ui.CB_auto_answer->setEnabled(false);
		ui.WG_adder->setEnabled(false);
	}
	else {
		ui.CB_auto_answer->setEnabled(true);
		ui.WG_adder->setEnabled(true);
	}
}

void MathTopicConf::on_CB_auto_answer_toggled(bool) {
	ui.WG_adder->AutoAnswerSwitch(ui.CB_auto_answer->isChecked());
	ui.WG_waitting->AutoAnswerSwitch(ui.CB_auto_answer->isChecked());
}

void MathTopicConf::AddFormula(const std::string& formula_str) {
	int left = 0, oper = 0, right = 0, answer = 0;
	std::size_t opr_pos = -1;
	if (formula_str.find('+') != -1) {
		opr_pos = formula_str.find('+');
		oper = 1;
	}
	else if (formula_str.find('-') != -1) {
		opr_pos = formula_str.find('-');
		oper = 2;
	}
	else if (formula_str.find('*') != -1) {
		opr_pos = formula_str.find('*');
		oper = 3;
	}
	else if (formula_str.find('/') != -1) {
		opr_pos = formula_str.find('/');
		oper = 4;
	}
	if (opr_pos != -1) {
		left = boost::lexical_cast<int>(formula_str.substr(0, opr_pos));
		std::size_t equal_pos = formula_str.find('=');
		right = boost::lexical_cast<int>(formula_str.substr(opr_pos+1 , equal_pos-opr_pos-1));
		answer = boost::lexical_cast<int>(formula_str.substr(equal_pos + 1, formula_str.size() - equal_pos-1));
	}
	ui.WG_waitting->AddQuestion(left, oper, right, answer);
}

int MathTopicConf::SaveFormulas(bool is_override) {
	std::ifstream file;
	file.open(MathSubjectsPath, std::ios::in);
	if (!file.is_open()) {
		return -1;
	}
	nlohmann::json js;
	file >> js;
	file.close();

	nlohmann::json::iterator find_base = js.find("MathSubjects");
	if (find_base == js.cend()) {
		return -2;
	}
	std::string subject_name = ui.LE_name->text().toStdString();
	nlohmann::json::iterator find = find_base->find(subject_name);
	if (find != find_base->cend()) {
		if (!_is_editing && !is_override) {
			_override_ptr->showDialog();
			return -1;
		}
		find_base->erase(find);
	}

	std::vector<FORMULA> formulas;
	if (!ui.WG_waitting->GetQuestions(formulas)) {
		return -3;
	}
	for (std::vector<FORMULA>::const_iterator itr = formulas.cbegin(); itr != formulas.cend(); ++itr) {
		js["MathSubjects"][subject_name].push_back(Formula2Str(*itr));
	}

	std::fstream file_out;
	file_out.open(MathSubjectsPath, std::ios::out);
	if (!file_out.is_open()) {
		return -4;
	}
	file_out << std::setw(4) << js << std::endl;
	file_out.close();


	return 0;
}

std::string MathTopicConf::Formula2Str(const FORMULA& formula) {
	std::string over_str;

	over_str += boost::lexical_cast<std::string>(formula.left);
	switch (formula.oper){
		case 1:	over_str += '+';	break;
		case 2:	over_str += '-';	break;
		case 3:	over_str += '*';	break;
		case 4:	over_str += '/';	break;
		default: return "";
	}
	over_str += boost::lexical_cast<std::string>(formula.right);
	over_str += '=';
	over_str += boost::lexical_cast<std::string>(formula.answer);

	return over_str;
}
