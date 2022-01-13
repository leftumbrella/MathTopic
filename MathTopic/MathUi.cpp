#include "MathUi.h"

void MathUi::keyPressEvent(QKeyEvent* event) {
	
	switch (event->key())
	{
	case Qt::Key_Space: 
		Next();
		break;
	case Qt::Key_Enter:
	case Qt::Key_Return:
		Commit();
		break;
	case Qt::Key_Delete:	
		ui.lb_answer->setText(""); 
		Reset();
		break;
	case Qt::Key_Backspace: 
		ui.lb_answer->setText(ui.lb_answer->text().left(ui.lb_answer->text().length() - 1));
		Reset();
		break;
	case Qt::Key_Period:
		if (ui.lb_answer->text().indexOf('.') == -1)
			ui.lb_answer->setText(ui.lb_answer->text() + '.');
		Reset();
		break;
	case Qt::Key_Minus:
		if (ui.lb_answer->text().isEmpty())
			ui.lb_answer->setText(ui.lb_answer->text() + '-');
		Reset();
		break;
	case Qt::Key_0:	ui.lb_answer->setText(ui.lb_answer->text() + '0'); Reset();break;
	case Qt::Key_1:	ui.lb_answer->setText(ui.lb_answer->text() + '1'); Reset();break;
	case Qt::Key_2:	ui.lb_answer->setText(ui.lb_answer->text() + '2'); Reset();break;
	case Qt::Key_3:	ui.lb_answer->setText(ui.lb_answer->text() + '3'); Reset();break;
	case Qt::Key_4:	ui.lb_answer->setText(ui.lb_answer->text() + '4'); Reset();break;
	case Qt::Key_5:	ui.lb_answer->setText(ui.lb_answer->text() + '5'); Reset();break;
	case Qt::Key_6:	ui.lb_answer->setText(ui.lb_answer->text() + '6'); Reset();break;
	case Qt::Key_7:	ui.lb_answer->setText(ui.lb_answer->text() + '7'); Reset();break;
	case Qt::Key_8:	ui.lb_answer->setText(ui.lb_answer->text() + '8'); Reset();break;
	case Qt::Key_9:	ui.lb_answer->setText(ui.lb_answer->text() + '9'); Reset();break;
	default:
		break;
	}
	QWidget::keyPressEvent(event);
}

void MathUi::showEvent(QShowEvent* event) {
	QWidget::showEvent(event);
	if (ConfigCore::instance()->ReadValue("BaseSetting", "KeyDialog", nullptr) == "false") {
		ui.widget_6->hide();
	}
	else {
		ui.widget_6->show();
	}
	_question_num = 1;
	Next(true);
}

MathUi::MathUi(QWidget* parent)
	: QWidget(parent), _question_num(1)
	, _btn_home_ptr(new QtMaterialFloatingActionButton(QIcon(":/Resources/image/home.png"), this))
	, _btn_close_ptr(new QtMaterialFloatingActionButton(QIcon(":/Resources/image/close.png"), this))
	, _home_dialog_ptr(new QtMaterialDialog(this))
	, _close_dialog_ptr(new QtMaterialDialog(this))
	, _snackbar(new QtMaterialSnackbar(this))
	, _model(Random), _is_commited(false)
	, _ok_num(0), _error_num(0), _subject_start_time(0)
{
	ui.setupUi(this);

	ui.btn_all_star->setIcon(QIcon(":/Resources/image/star.png"));
	ui.btn_all_star->setColor(Qt::yellow);

	ui.btn_all_star->setFocusPolicy(Qt::NoFocus);
	_btn_home_ptr->setFocusPolicy(Qt::NoFocus);
	_btn_close_ptr->setFocusPolicy(Qt::NoFocus);
	ui.btn_hideKey->setFocusPolicy(Qt::NoFocus);
	ui.btn_commit->setFocusPolicy(Qt::NoFocus);
	ui.btn_next->setFocusPolicy(Qt::NoFocus);
	ui.btn_star->setFocusPolicy(Qt::NoFocus);

	_btn_home_ptr->setToolTip(QStringLiteral("主页"));
	_btn_close_ptr->setToolTip(QStringLiteral("关闭软件"));

	ui.btn_commit->setIcon(QIcon(":/Resources/image/commit.png"));
	ui.btn_next->setIcon(QIcon(":/Resources/image/next.png"));
	ui.btn_hideKey->setIcon(QIcon(":/Resources/image/hide.png"));
	connect(ui.btn_hideKey, &QtMaterialRaisedButton::clicked, this, &MathUi::HideKey);

	_btn_home_ptr->setCorner(Qt::TopLeftCorner);
	_btn_home_ptr->setBackgroundColor("#168570");
	_btn_home_ptr->setParent(ui.widget_3);

	_btn_close_ptr->setCorner(Qt::TopRightCorner);
	_btn_close_ptr->setBackgroundColor("#973444");
	_btn_close_ptr->setParent(ui.widget_3);

	{// 设置对话框
		QVBoxLayout* dialogLayout = new QVBoxLayout;
		_home_dialog_ptr->setWindowLayout(dialogLayout);

		QWidget* WG_dialog = new QWidget(_home_dialog_ptr);
		QVBoxLayout* LY_dialog = new QVBoxLayout;
		WG_dialog->setLayout(LY_dialog);
		QtMaterialFlatButton* btn_ok = new QtMaterialFlatButton(QStringLiteral("没错"));
		QtMaterialFlatButton* btn_cancel = new QtMaterialFlatButton(QStringLiteral("不要"));

		connect(btn_ok, &QtMaterialFlatButton::clicked, this, [=]() {
			_home_dialog_ptr->hideDialog();
			QPlaySound(3);
			emit GoWelcome();
			});
		connect(btn_cancel, &QtMaterialFlatButton::clicked, _home_dialog_ptr, &QtMaterialDialog::hideDialog);
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

		QWidget* WG_dia_btns = new QWidget(_home_dialog_ptr);
		QHBoxLayout* LY_dia_btns = new QHBoxLayout;
		WG_dia_btns->setLayout(LY_dia_btns);
		LY_dia_btns->addWidget(btn_ok);
		LY_dia_btns->addWidget(btn_cancel);

		label_ptr->setText(QStringLiteral("要回到主界面了嘛？"));
		LY_dialog->addWidget(label_ptr);
		LY_dialog->addSpacing(1);
		LY_dialog->addWidget(WG_dia_btns);
		LY_dialog->setAlignment(label_ptr, Qt::AlignTop | Qt::AlignCenter);


		dialogLayout->addWidget(WG_dialog);

		connect(_btn_home_ptr, &QtMaterialFloatingActionButton::clicked, _home_dialog_ptr, &QtMaterialDialog::showDialog);
		connect(_btn_home_ptr, &QtMaterialFloatingActionButton::clicked, this, [=]() {
			QPlaySound(4);
			});
	}
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

	ui.btn_next->setBackgroundColor("#93b469");
	ui.btn_commit->setBackgroundColor("#93b469");

	ui.btn_star->setIcon(QIcon(""));
	ui.btn_star->setIconSize(QSize(50, 50));
	ui.LB_info->setText("");
	Initialize();
	Next(true);
}

MathUi::~MathUi()
{
}

void MathUi::load(const QString& name) {
	_formulas.clear();
	_ok_num = _error_num = 0;
	_is_commited = false;
	_sub_name = name;
	_model = Subject;
	
	std::vector<FORMULA> formulas;
	if (JsonMath::instance()->ReadFormulas(formulas, name.toStdString())) {
		for (const auto& formula : formulas) {
			_formulas.push_back(std::make_pair(formula, 0));
		}
	}

	_subject_start_time = clock();
	ui.LB_all_star->setText(" X 0");
}

void MathUi::HideKey() {
	QPlaySound(3);
	ui.widget_6->hide();
	ConfigCore::instance()->SetValue(false, "BaseSetting", "KeyDialog", nullptr);
}

void MathUi::on_btn_next_clicked() {
	QPlaySound(3);
	Next();
}

void MathUi::on_btn_commit_clicked() {
	Commit();
}

void MathUi::Commit() {
	if (_is_commited) {
		return;
	}
	_is_commited = true;
	int real_answer = 0;
	if (IsRealAnswer(real_answer)) {
		if (_formulas[_question_num - 1].second == 0) {
			_ok_num += 1;
			_formulas[_question_num - 1].second = 1;
			ui.btn_all_star->toggle();
			ui.LB_all_star->setText(QString(" X %1").arg(_ok_num));
			StatisticsUseTime();
			StatisticsPlusNum(true);
		}		
		ui.btn_star->setIcon(QIcon(":/Resources/image/star.png"));

		ui.btn_star->setColor(Qt::yellow);
		ui.btn_star->click();
		QPlaySound(1);
		
		if (ConfigCore::instance()->ReadValue("BaseSetting", "CommitSkip", nullptr) == "true") {
			Next();
		}
	}
	else {
		if (_formulas[_question_num - 1].second == 0) {
			_error_num += 1;
			_formulas[_question_num - 1].second = 2;
		}
		StatisticsPlusNum(false);
		ui.btn_star->setIcon(QIcon(":/Resources/image/question_area.png"));
		ui.btn_star->setColor("#a22041");
		ui.btn_star->click();
		QString info_str = QStringLiteral("正确答案是 “%1” 哦！").arg(real_answer);
		int res = ui.WG_animal->setAnimal(_formulas[_question_num - 1].first.left
			, _formulas[_question_num - 1].first.oper, _formulas[_question_num - 1].first.right);
		if (res) {
			ui.WG_animal->show();
			info_str += QStringLiteral("快看看提示吧！");
		}
		
		ui.LB_info->setText(info_str);
		QPlaySound(2);
	}
}

void MathUi::Next(bool system_skip) {
	if ( ConfigCore::instance()->ReadValue("BaseSetting", "ErrorSkip", nullptr) == "false") {
		int real = 0;
		if (!system_skip) {
			if (!IsRealAnswer(real)) {
				_snackbar->addMessage(QStringLiteral("当前结果与正确答案不符\n无法进行下一题"));
				return;
			}
		}
	}

	if (!_is_commited && !system_skip) {
		int real = 0;
		if (IsRealAnswer(real)) {
			++_ok_num;
			StatisticsPlusNum(true);
			StatisticsUseTime();
		}
		else {
			StatisticsPlusNum(false);
		}
	}

	if (!system_skip) {
		++_question_num;
	}
	ui.LB_question_num->setText(QString("%1-%2").arg(_question_num).arg(_formulas.size()));

	ui.WG_Main->setStyleSheet("color:black"); 
	ui.btn_star->setIcon(QIcon());
	ui.lb_answer->setText("");
	if (_model == Subject) {
		if (_formulas.size() < _question_num) {
			emit MathOver(_sub_name, _ok_num,_formulas.size()-_ok_num, clock() - _subject_start_time);
			return;
		}
		ui.lb_left->setText(QString::number(_formulas[_question_num - 1].first.left));
		switch (_formulas[_question_num - 1].first.oper) {
		case 1:
			_cal_type = Addition;
			ui.lb_operator->setText("+");
			break;
		case 2:
			_cal_type = Subtraction;
			ui.lb_operator->setText("-");
			break;
		case 3:
			_cal_type = Multiplication;
			ui.lb_operator->setText("X");
			break;
		case 4:
			_cal_type = Division;
			ui.lb_operator->setText(QString(247));
			break;
		}
		ui.lb_right->setText(QString::number(_formulas[_question_num - 1].first.right));
	}
	else if (_model == Random) {
		JudgeOperator();
		int left_num = JudgeLeft(_cal_type);
		ui.lb_left->setText(QString::number(left_num));
		ui.lb_right->setText(QString::number(JudgeRight(_cal_type, left_num)));
	}

	_start_time = clock();

	Reset();
}

void MathUi::Initialize() {
	if (ConfigCore::instance()->ReadValue("Setting", "Addition", "Switch", nullptr) == "true") {
		_cal_type = Addition;
	}
	else if (ConfigCore::instance()->ReadValue("Setting", "Subtraction", "Switch", nullptr) == "true") {
		_cal_type = Subtraction;
	}
	else if (ConfigCore::instance()->ReadValue("Setting", "Multiplication", "Switch", nullptr) == "true") {
		_cal_type = Multiplication;
	}
	else {
		_cal_type = Division;
	}
}

void MathUi::StatisticsUseTime() {
	std::time_t use_time = clock() - _start_time;
	std::string max_str = ConfigCore::instance()->ReadValue("Statistics", "Time", "MaxTime", nullptr);
	std::time_t max_time = 0;
	if (!max_str.empty()) {
		max_time = boost::lexical_cast<std::time_t>(max_str);
	}
	if (use_time > max_time) {
		ConfigCore::instance()->SetValue(use_time, "Statistics", "Time", "MaxTime", nullptr);
	}
	std::string min_str = ConfigCore::instance()->ReadValue("Statistics", "Time", "MinTime", nullptr);
	std::time_t min_time = 999999;
	if (!min_str.empty()) {
		min_time = boost::lexical_cast<std::time_t>(min_str);
	}
	if (use_time < min_time) {
		ConfigCore::instance()->SetValue(use_time, "Statistics", "Time", "MinTime", nullptr);
	}
}

void MathUi::StatisticsPlusNum(bool is_ok) {
	std::size_t over_num = 0;
	std::size_t error_num = 0;
	std::size_t ok_num = 0;
	std::string over_str = ConfigCore::instance()->ReadValue("Statistics", "Number", "OverQuestionNum", nullptr);
	std::string error_str = ConfigCore::instance()->ReadValue("Statistics", "Number", "ErrorQuestionNum", nullptr);
	std::string ok_str = ConfigCore::instance()->ReadValue("Statistics", "Number", "OkQuestionNum", nullptr);
	if (!over_str.empty()) {
		over_num = boost::lexical_cast<std::size_t>(over_str);
	}
	if (!error_str.empty()) {
		error_num = boost::lexical_cast<std::size_t>(error_str);
	}
	if (!ok_str.empty()) {
		ok_num = boost::lexical_cast<std::size_t>(ok_str);
	}
	ConfigCore::instance()->SetValue(over_num+1, "Statistics", "Number", "OverQuestionNum", nullptr);

	std::string key_str;
	switch (_cal_type) {
	case Addition:	key_str = "Addition";	break;
	case Subtraction:	key_str = "Subtraction";	break;
	case Multiplication:	key_str = "Multiplication";	break;
	case Division:	key_str = "Division";	break;
	}

	std::size_t opt_ok_num = 0;
	std::size_t opt_error_num = 0;

	std::string opt_num_str_ok = ConfigCore::instance()->ReadValue("Statistics", "Number", key_str.c_str(), "OkQuestionNum", nullptr);
	std::string opt_num_str_error = ConfigCore::instance()->ReadValue("Statistics", "Number", key_str.c_str(), "ErrorQuestionNum", nullptr);
	if (!opt_num_str_ok.empty()) {
		opt_ok_num = boost::lexical_cast<std::size_t>(opt_num_str_ok);
	}
	if (!opt_num_str_error.empty()) {
		opt_error_num = boost::lexical_cast<std::size_t>(opt_num_str_error);
	}
	ok_num = error_num = 0;
	error_str = ConfigCore::instance()->ReadValue("Statistics", "Number", key_str.c_str(),"ErrorQuestionNum", nullptr);
	ok_str = ConfigCore::instance()->ReadValue("Statistics", "Number", key_str.c_str(),"OkQuestionNum", nullptr);
	if (!ok_str.empty()) {
		ok_num = boost::lexical_cast<std::size_t>(ok_str);
	}
	if (!error_str.empty()) {
		error_num = boost::lexical_cast<std::size_t>(error_str);
	}

	if (is_ok) {
		ConfigCore::instance()->SetValue(ok_num+1, "Statistics", "Number", "OkQuestionNum", nullptr);
		ConfigCore::instance()->SetValue(opt_ok_num+1, "Statistics", "Number", key_str.c_str(), "OkQuestionNum", nullptr);
	}
	else {
		ConfigCore::instance()->SetValue(error_num+1, "Statistics", "Number", "ErrorQuestionNum", nullptr);
		ConfigCore::instance()->SetValue(opt_error_num+1, "Statistics", "Number", key_str.c_str(), "ErrorQuestionNum", nullptr);
	}
}

int MathUi::RadomNumber(int min, int max) {
	std::default_random_engine eng(std::random_device{}());
	std::uniform_int_distribution<int> radom(min, max);
	return radom(eng);
}

bool MathUi::HaveLess(CalType cal_type) {
	std::string cal_str;
	switch (cal_type)
	{
	case Addition:	cal_str = "Addition";	break;
	case Subtraction:	cal_str = "Subtraction";	break;
	case Multiplication:	cal_str = "Multiplication";	break;
	case Division:	cal_str = "Division";	break;
	}
	return ConfigCore::instance()->ReadValue("Setting", cal_str.c_str(), "HaveLess", nullptr) == "true";
}

int MathUi::GetMax(CalType cal_type) {
	std::string cal_str;
	switch (cal_type)
	{
	case Addition:	cal_str = "Addition";	break;
	case Subtraction:	cal_str = "Subtraction";	break;
	case Multiplication:	cal_str = "Multiplication";	break;
	case Division:	cal_str = "Division";	break;
	}
	std::string max_str = ConfigCore::instance()->ReadValue("Setting", cal_str.c_str(), "MaxNumber", nullptr);

	int number = 10;
	if (!max_str.empty()) {
		number = boost::lexical_cast<int>(max_str);
	}
	return number;
}

void MathUi::JudgeOperator() {
	int tmp_type = _cal_type;
	while (true) {
		tmp_type++;
		if (tmp_type > 4) {
			tmp_type = 1;
		}
		if (tmp_type == _cal_type) {
			break;
		}
		switch (tmp_type)
		{
		case Addition:
			if (ConfigCore::instance()->ReadValue("Setting", "Addition", "Switch", nullptr) != "true") {
				continue;
			}
			break;
		case Subtraction:
			if (ConfigCore::instance()->ReadValue("Setting", "Subtraction", "Switch", nullptr) != "true") {
				continue;
			}
			break;
		case Multiplication:
			if (ConfigCore::instance()->ReadValue("Setting", "Multiplication", "Switch", nullptr) != "true") {
				continue;
			}
			break;
		case Division:
			if (ConfigCore::instance()->ReadValue("Setting", "Division", "Switch", nullptr) != "true") {
				continue;
			}
			break;
		}
		break;
	}
	switch (tmp_type)
	{
	case Addition:
		_cal_type = Addition;
		ui.lb_operator->setText("+");
		break;
	case Subtraction:
		_cal_type = Subtraction;
		ui.lb_operator->setText("-");
		break;
	case Multiplication:
		_cal_type = Multiplication;
		ui.lb_operator->setText("X");
		break;
	case Division:
		_cal_type = Division;
		ui.lb_operator->setText(QString(247));
		break;
	}
}

int MathUi::JudgeLeft(CalType cal_type) {
	int num_max = GetMax(cal_type);
	if (HaveLess(cal_type)) {
		return RadomNumber(0, num_max - 1);
	}

	return RadomNumber(num_max / 10, num_max - 1);
}

int MathUi::JudgeRight(CalType cal_type, int left_num) {

	// 加法与乘法无需特殊处理
	if (cal_type == Addition || cal_type == Multiplication) {
		return JudgeLeft(cal_type);
	}

	if (cal_type == Subtraction) {
		bool hasNegative = ConfigCore::instance()->ReadValue("Setting", "Subtraction", "HasNegative", nullptr) == "true";

		if (hasNegative) {
			return JudgeLeft(cal_type);
		}

		if (HaveLess(cal_type)) {
			return RadomNumber(0, left_num);
		}
		int max_num = GetMax(cal_type);
		return RadomNumber(max_num / 10, left_num);
	}


	if (cal_type == Division) {
		bool than_zero = ConfigCore::instance()->ReadValue("Setting", "Division", "ThanZero", nullptr) == "true";
		bool have_remainder = ConfigCore::instance()->ReadValue("Setting", "Division", "HasRemainder", nullptr) == "true";
		if (have_remainder) {
			if (than_zero) {
				return RadomNumber(1, left_num);
			}
			else {

				return JudgeLeft(cal_type);
			}
		}
		else {
			int max = GetMax(cal_type);
			std::time_t start_time = clock();
			while (true)
			{
				if (clock() - start_time > 3000) {
					return 1;
				}
				int right = 1;
				right = RadomNumber(1, max);
				if (left_num % right == 0) {
					return right;
				}
			}

		}
	}
	return 0;
}

bool MathUi::IsRealAnswer(int& answer_) {
	
	if (ui.lb_answer->text().isEmpty()) {
		if (_formulas.size() >=_question_num && _question_num!=0) {
			answer_ = _formulas[_question_num - 1].first.answer;
		}
		return false;
	}
	int real_answer = 0;
	bool is_real = false;

	QString answer = ui.lb_answer->text();
	if (_model == Subject) {
		answer_ = _formulas[_question_num - 1].first.answer;
		return answer.toInt() == answer_;
	}
	int left = ui.lb_left->text().toInt();
	int right = ui.lb_right->text().toInt();

	QString operator_str = ui.lb_operator->text();
	switch (_cal_type)
	{
	case Addition:	real_answer = left + right;		break;
	case Subtraction:	real_answer = left - right;	break;
	case Multiplication:	real_answer = left * right;	break;
	case Division: {
		double answer_double = left * 1.0 / right;
		if (answer.toDouble() == answer_double) {
			is_real = true;
			break;
		}
		QString real_str = QString::number(answer_double);
		int decimal = boost::lexical_cast<int>(ConfigCore::instance()->ReadValue("Setting", "Division", "NumberDecimal", nullptr));
		if (answer.indexOf('.') == -1 || answer.length() < decimal + answer.indexOf('.') + 1) {
			break;
		}
		bool look_point = false;
		int num_point = 0;
		for (int i = 0; i < real_str.size(); ++i) {
			if (answer[i] != real_str[i]) {
				break;
			}
			if (look_point) {
				num_point++;
				if (num_point == decimal) {
					is_real = true;
					break;
				}
			}
			if (answer[i] == '.') {
				look_point = true;
			}
		}
		break;
	}
	}



	if (_cal_type != Division && real_answer == answer.toInt()) {
		is_real = true;
	}

	answer_ = real_answer;

	return is_real;
}

FORMULA MathUi::Str2Formula(const std::string& str) {
	FORMULA formula;
	std::size_t opr_pos = -1;
	if (str.find('+') != -1) {
		opr_pos = str.find('+');
		formula.oper = 1;
	}
	else if (str.find('-') != -1) {
		opr_pos = str.find('-');
		formula.oper = 2;
	}
	else if (str.find('*') != -1) {
		opr_pos = str.find('*');
		formula.oper = 3;
	}
	else if (str.find('/') != -1) {
		opr_pos = str.find('/');
		formula.oper = 4;
	}
	if (opr_pos != -1) {
		formula.left = boost::lexical_cast<int>(str.substr(0, opr_pos));
		std::size_t equal_pos = str.find('=');
		formula.right = boost::lexical_cast<int>(str.substr(opr_pos + 1, equal_pos - opr_pos - 1));
		formula.answer = boost::lexical_cast<int>(str.substr(equal_pos + 1, str.size() - equal_pos - 1));
	}
	return formula;
}

void MathUi::Reset() {
	ui.btn_star->setIcon(QIcon());
	ui.LB_info->setText(""); 
	_is_commited = false;
	ui.WG_animal->hide();
}
