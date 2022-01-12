#include "SubjectList.h"

extern std::string MathSubjectsPath;

SubjectList::SubjectList(QWidget *parent)
	: QWidget(parent)
	, _btn_close_ptr(new QtMaterialFloatingActionButton(QIcon(":/MathTopic/close.png"), this))
	, _btn_home_ptr(new QtMaterialFloatingActionButton(QIcon(":/MathTopic/home.png"), this))
	, _close_dialog_ptr(new QtMaterialDialog(this))
{
	ui.setupUi(this);

	ui.btn_add->setBackgroundColor("#168570");

	connect(ui.WG_Subjects, &SubjectsUi::SubjectSelect, this, &SubjectList::SubjectSelect);
	ui.btn_add->setIcon(QIcon(":/MathTopic/add_new.png"));

	_btn_close_ptr->setCorner(Qt::TopRightCorner);
	_btn_close_ptr->setBackgroundColor("#973444");

	_btn_home_ptr->setCorner(Qt::TopLeftCorner);
	_btn_home_ptr->setBackgroundColor("#168570");

	_btn_home_ptr->setToolTip(QStringLiteral("主页"));
	_btn_close_ptr->setToolTip(QStringLiteral("关闭软件"));

	connect(_btn_home_ptr, &QtMaterialFloatingActionButton::clicked, this, [=]() {
		QPlaySound(3);
		emit GoHome();
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

SubjectList::~SubjectList()
{
}

void SubjectList::showEvent(QShowEvent* event) {
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

void SubjectList::on_btn_add_clicked() {
	QPlaySound(3);
	emit SubjectNew();
}
