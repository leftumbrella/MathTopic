#include "QustionMathUi.h"

QustionMathUi::QustionMathUi(QWidget *parent)
	: QWidget(parent)
	, _dialog_ptr(new QtMaterialDialog(this))
{
	ui.setupUi(this);
	ui.btn_return->setIcon(QIcon(":/Resources/image/return.png"));
	ui.btn_return->setBackgroundColor("#9bae86");
	ui.btn_start->setIcon(QIcon(":/Resources/image/start.png"));
	ui.btn_start->setBackgroundColor("#a381ba");
	connect(ui.btn_return, &QtMaterialRaisedButton::clicked, this, &QustionMathUi::Return);
	connect(ui.btn_return, &QtMaterialRaisedButton::clicked, this, [=]() {
		QPlaySound(3);
		});


	ui.CB_division_hasRemainder->setCheckedColor("#90caaf");
	ui.CB_opt_addition->setCheckedColor("#90caaf");
	ui.CB_opt_subtraction->setCheckedColor("#90caaf");
	ui.CB_opt_multiplication->setCheckedColor("#90caaf");
	ui.CB_opt_division->setCheckedColor("#90caaf");
	ui.CB_subtraction_hasNegative->setCheckedColor("#90caaf");
	ui.CB_division_thanZero->setCheckedColor("#90caaf");


	{// 设置对话框
		QVBoxLayout* dialogLayout = new QVBoxLayout;
		_dialog_ptr->setWindowLayout(dialogLayout);

		QWidget* WG_dialog = new QWidget(_dialog_ptr);
		QVBoxLayout* LY_dialog = new QVBoxLayout;
		WG_dialog->setLayout(LY_dialog);
		QtMaterialFlatButton* btn_ok = new QtMaterialFlatButton(QStringLiteral("我要重新选择"));

		connect(btn_ok, &QtMaterialFlatButton::clicked, this, [=]() {
			_dialog_ptr->hideDialog();
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

		QWidget* WG_dia_btns = new QWidget(_dialog_ptr);
		QHBoxLayout* LY_dia_btns = new QHBoxLayout;
		WG_dia_btns->setLayout(LY_dia_btns);
		LY_dia_btns->addWidget(btn_ok);
		
		label_ptr->setText(QStringLiteral("当前未选择任何算术类型，无法开始!"));
		LY_dialog->addWidget(label_ptr);
		LY_dialog->addSpacing(1);
		LY_dialog->addWidget(WG_dia_btns);
		LY_dialog->setAlignment(label_ptr, Qt::AlignTop | Qt::AlignCenter);


		dialogLayout->addWidget(WG_dialog);
	}

}

QustionMathUi::~QustionMathUi()
{
}

void QustionMathUi::showEvent(QShowEvent* eve) {
	QWidget::showEvent(eve);

	if (ConfigCore::instance()->ReadValue("Setting", "Addition", "Switch", nullptr).empty()) {
		return;
	}

	ui.CB_opt_addition->setChecked(ConfigCore::instance()->ReadValue("Setting", "Addition", "Switch", nullptr) == "true");
	ui.LE_addition_max->setText(QString::fromStdString(ConfigCore::instance()->ReadValue("Setting", "Addition", "MaxNumber", nullptr)));

	ui.CB_opt_subtraction->setChecked(ConfigCore::instance()->ReadValue("Setting", "Subtraction", "Switch", nullptr) == "true");
	ui.LE_subtraction_max->setText(QString::fromStdString(ConfigCore::instance()->ReadValue("Setting", "Subtraction", "MaxNumber", nullptr)));
	ui.CB_subtraction_hasNegative->setChecked(ConfigCore::instance()->ReadValue("Setting", "Subtraction", "HasNegative", nullptr) == "true");

	ui.CB_opt_multiplication->setChecked(ConfigCore::instance()->ReadValue("Setting", "Multiplication", "Switch", nullptr) == "true");
	ui.LE_multiplication_max->setText(QString::fromStdString(ConfigCore::instance()->ReadValue("Setting", "Multiplication", "MaxNumber", nullptr)));

	ui.CB_opt_division->setChecked(ConfigCore::instance()->ReadValue("Setting", "Division", "Switch", nullptr) == "true");
	ui.LE_division_max->setText(QString::fromStdString(ConfigCore::instance()->ReadValue("Setting", "Division", "MaxNumber", nullptr)));
	ui.CB_division_thanZero->setChecked(ConfigCore::instance()->ReadValue("Setting", "Division", "ThanZero", nullptr) == "true");
	ui.CB_division_hasRemainder->setChecked(ConfigCore::instance()->ReadValue("Setting", "Division", "HasRemainder", nullptr) == "true");
	ui.SB_division_number_decimal->setValue(boost::lexical_cast<int>(ConfigCore::instance()->ReadValue("Setting", "Division", "NumberDecimal", nullptr)));
}

void QustionMathUi::on_btn_start_clicked() {

	QPlaySound(3);

	if (!ui.CB_opt_addition->isChecked() && !ui.CB_opt_subtraction->isChecked()
		&& !ui.CB_opt_multiplication->isChecked() && !ui.CB_opt_division->isChecked()) {
		_dialog_ptr->showDialog();
		return;
	}


	ConfigCore::instance()->SetValue(ui.CB_opt_addition->isChecked(), "Setting", "Addition", "Switch", nullptr);
	ConfigCore::instance()->SetValue(ui.LE_addition_max->text().toInt(), "Setting", "Addition", "MaxNumber", nullptr);

	ConfigCore::instance()->SetValue(ui.CB_opt_subtraction->isChecked(), "Setting", "Subtraction", "Switch", nullptr);
	ConfigCore::instance()->SetValue(ui.LE_subtraction_max->text().toInt(), "Setting", "Subtraction", "MaxNumber", nullptr);
	ConfigCore::instance()->SetValue(ui.CB_subtraction_hasNegative->isChecked(), "Setting", "Subtraction", "HasNegative", nullptr);

	ConfigCore::instance()->SetValue(ui.CB_opt_multiplication->isChecked(), "Setting", "Multiplication", "Switch", nullptr);
	ConfigCore::instance()->SetValue(ui.LE_multiplication_max->text().toInt(), "Setting", "Multiplication", "MaxNumber", nullptr);

	ConfigCore::instance()->SetValue(ui.CB_opt_division->isChecked(), "Setting", "Division", "Switch", nullptr);
	ConfigCore::instance()->SetValue(ui.LE_division_max->text().toInt(), "Setting", "Division", "MaxNumber", nullptr);
	ConfigCore::instance()->SetValue(ui.CB_division_thanZero->isChecked(), "Setting", "Division", "ThanZero", nullptr);
	ConfigCore::instance()->SetValue(ui.CB_division_hasRemainder->isChecked(), "Setting", "Division", "HasRemainder", nullptr);
	ConfigCore::instance()->SetValue(ui.SB_division_number_decimal->value(), "Setting", "Division", "NumberDecimal", nullptr);

	emit StartMath();
	
}
