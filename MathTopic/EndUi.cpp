#include "EndUi.h"

void EndUi::ChangeOver(const QString& subname ,int ok_num, int error_num, std::time_t time) {
	_sub_name = subname;
	QString over_str = QStringLiteral("当前科目 “%1” 一共有 %2 道题目；\n答对了 %3 道；\n答错了 %4 道；\n")
		.arg(_sub_name).arg(ok_num+error_num).arg(ok_num).arg(error_num);
	if (error_num == 0) {
		over_str += QStringLiteral("很棒啊!!\n");
	}
	else {
		over_str += QStringLiteral("还要继续加油哦!\n\n");
	}

	over_str += QStringLiteral("总共花费时间是 %1 秒；\n平均每道题 %2 秒！")
		.arg(QString::number(time / 1000.0 ,'f' ,3)).arg(QString::number(time / 1000.0 / (ok_num + error_num), 'f', 3));
	
	ui.LB_all->setText(over_str);

	ui.LB_all_star->setText(QString(" + %1").arg(ok_num));
}

EndUi::EndUi(QWidget *parent)
	: QWidget(parent)
	, _btn_close_ptr(new QtMaterialFloatingActionButton(QIcon(":/Resources/image/close.png"), this))
	, _close_dialog_ptr(new QtMaterialDialog(this))
{
	ui.setupUi(this);

	ui.btn_all_star->setIcon(QIcon(":/Resources/image/star.png"));
	ui.btn_all_star->setIconSize(QSize(50, 50));
	ui.btn_all_star->setColor(Qt::yellow);

	_btn_close_ptr->setToolTip(QStringLiteral("关闭软件"));

	ui.btn_home->setBackgroundColor("#168570");
	ui.btn_again->setBackgroundColor("#a381ba");

	ui.btn_home->setIcon(QIcon(":/Resources/image/home.png"));
	ui.btn_again->setIcon(QIcon(":/Resources/image/retry.png"));
	connect(ui.btn_home, &QtMaterialRaisedButton::clicked, this, &EndUi::GoHome);
	connect(ui.btn_again, &QtMaterialRaisedButton::clicked, this, [=]() {
		QPlaySound(3);
		emit ReTry(_sub_name);
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

}

EndUi::~EndUi()
{
}
