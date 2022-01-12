#include "StatisticsUi.h"

StatisticsUi::StatisticsUi(QWidget *parent)
	: QWidget(parent)
	, _btn_home_ptr(new QtMaterialFloatingActionButton(QIcon(":/Resources/image/home.png"), this))
{
	ui.setupUi(this);
	_btn_home_ptr->setCorner(Qt::TopLeftCorner);
	_btn_home_ptr->setBackgroundColor("#168570");

	connect(_btn_home_ptr, &QtMaterialFloatingActionButton::clicked, this, [=]() {
		QPlaySound(3);
		emit GoWelcome();
		});
	ui.btn_all_star->setIcon(QIcon(":/Resources/image/star.png"));
	ui.btn_all_star->setIconSize(QSize(50, 50));
	ui.btn_all_star->setColor(Qt::yellow);

	_btn_home_ptr->setToolTip(QStringLiteral("主页"));
}

StatisticsUi::~StatisticsUi()
{
}

void StatisticsUi::showEvent(QShowEvent* event) {
	QWidget::showEvent(event);

	std::string max_time_str = ConfigCore::instance()->ReadValue("Statistics", "Time", "MaxTime", nullptr);
	if (max_time_str.empty()) {
		return;
	}

	std::string min_time_str = ConfigCore::instance()->ReadValue("Statistics", "Time", "MinTime", nullptr);

	ui.LB_time_max->setText(QString::number(QString::fromStdString(max_time_str).toULongLong() / 1000.0, 'f', 4));
	ui.LB_time_min->setText(QString::number(QString::fromStdString(min_time_str).toULongLong() / 1000.0, 'f', 4));

	ui.LB_num_over->setText(QString::fromStdString(
		ConfigCore::instance()->ReadValue("Statistics", "Number", "OverQuestionNum", nullptr)));
	ui.LB_num_ok->setText(QString::fromStdString(
		ConfigCore::instance()->ReadValue("Statistics", "Number", "OkQuestionNum", nullptr)));
	ui.LB_num_error->setText(QString::fromStdString(
		ConfigCore::instance()->ReadValue("Statistics", "Number", "ErrorQuestionNum", nullptr)));

	ui.LB_add_ok->setText(QString::fromStdString(
		ConfigCore::instance()->ReadValue("Statistics", "Number", "Addition", "OkQuestionNum", nullptr)));
	ui.LB_add_error->setText(QString::fromStdString(
		ConfigCore::instance()->ReadValue("Statistics", "Number", "Addition", "ErrorQuestionNum", nullptr)));

	ui.LB_sub_ok->setText(QString::fromStdString(
		ConfigCore::instance()->ReadValue("Statistics", "Number", "Subtraction", "OkQuestionNum", nullptr)));
	ui.LB_sub_error->setText(QString::fromStdString(
		ConfigCore::instance()->ReadValue("Statistics", "Number", "Subtraction", "ErrorQuestionNum", nullptr)));

	ui.LB_mut_ok->setText(QString::fromStdString(
		ConfigCore::instance()->ReadValue("Statistics", "Number", "Multiplication", "OkQuestionNum", nullptr)));
	ui.LB_mut_error->setText(QString::fromStdString(
		ConfigCore::instance()->ReadValue("Statistics", "Number", "Multiplication", "ErrorQuestionNum", nullptr)));

	ui.LB_dis_ok->setText(QString::fromStdString(
		ConfigCore::instance()->ReadValue("Statistics", "Number", "Division", "OkQuestionNum", nullptr)));
	ui.LB_dis_error->setText(QString::fromStdString(
		ConfigCore::instance()->ReadValue("Statistics", "Number", "Division", "ErrorQuestionNum", nullptr)));

	ui.LB_all_star->setText(QStringLiteral(" 数量为 : %1").arg(ui.LB_num_ok->text()) );
}
