#include "SubjectChooser.h"
extern std::string MathSubjectsPath;
SubjectChooser::SubjectChooser(QWidget *parent)
	: QWidget(parent)
	, _btn_close_ptr(new QtMaterialFloatingActionButton(QIcon(":/MathTopic/close.png"), this))
	, _btn_statistics_ptr(new QtMaterialFloatingActionButton(QIcon(":/MathTopic/actionstatistical.png"), this))
	, _btn_data_ptr(new QtMaterialFloatingActionButton(QIcon(":/MathTopic/data.png"), this))
	, _btn_setting_ptr(new QtMaterialFloatingActionButton(QIcon(":/MathTopic/setting.png"), this))
	, _close_dialog_ptr(new QtMaterialDialog(this))
{
	ui.setupUi(this);

	ui.WG_Subjects->NoDelete();

	connect(ui.WG_Subjects, &SubjectsUi::SubjectSelect, this, &SubjectChooser::GoSubject);


	_btn_close_ptr->setCorner(Qt::TopRightCorner);
	_btn_close_ptr->setBackgroundColor("#973444");
	_btn_close_ptr->setToolTip(QStringLiteral("关闭软件"));

	_btn_setting_ptr->setCorner(Qt::BottomLeftCorner);
	_btn_setting_ptr->setBackgroundColor("#1E2AD2");
	_btn_setting_ptr->setToolTip(QStringLiteral("设置"));

	_btn_statistics_ptr->setCorner(Qt::BottomRightCorner);
	_btn_statistics_ptr->setBackgroundColor("#FFA6B7");
	_btn_statistics_ptr->setToolTip(QStringLiteral("统计"));

	_btn_data_ptr->setCorner(Qt::TopLeftCorner);
	_btn_data_ptr->setBackgroundColor("#168570");
	_btn_data_ptr->setToolTip(QStringLiteral("科目编辑"));

	connect(_btn_setting_ptr, &QtMaterialFloatingActionButton::clicked, this, [=]() {
		QPlaySound(3);
		emit GoSetting();
		});
	connect(_btn_statistics_ptr, &QtMaterialFloatingActionButton::clicked, this, [=]() {
		QPlaySound(3);
		emit GoStatistics();
		});
	connect(_btn_data_ptr, &QtMaterialFloatingActionButton::clicked, this, [=]() {
		QPlaySound(3);
		emit GoData();
		});

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

SubjectChooser::~SubjectChooser()
{
}

void SubjectChooser::showEvent(QShowEvent* event) {
	QWidget::showEvent(event);

	ui.WG_Subjects->ClearAll();

	std::ifstream file;
	file.open(MathSubjectsPath, std::ios::in);
	if (!file.is_open()) {
		return;
	}
	nlohmann::json js;
	file >> js;
	file.close();
	nlohmann::json::const_iterator find = js.find("MathSubjects");
	if (find != js.cend()) {
		nlohmann::json::const_iterator itr;
		for (itr = find->cbegin(); itr != find->cend(); ++itr) {
			ui.WG_Subjects->AddSubject(QString::fromStdString(itr.key()));
		}
	}
}
