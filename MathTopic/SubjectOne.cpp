#include "SubjectOne.h"

SubjectOne::SubjectOne(const QString& name, QWidget* parent, bool have_delete)
	: QWidget(parent),_name(name)
{
	ui.setupUi(this);

	if (!have_delete) {
		ui.btn_delete->hide();
	}

	ui.btn_delete->setIcon(QIcon(":/Resources/image/delete.png"));
	ui.btn_delete->setColor("#89303f");
	ui.btn_delete->setIconSize(QSize(50, 50));
	ui.btn_subject->setText(_name);
	ui.btn_subject->setIcon(QIcon(":/Resources/image/subject.png"));
}

SubjectOne::~SubjectOne()
{
}

QString& SubjectOne::Name() {
	return _name;
}

void SubjectOne::on_btn_subject_clicked() {
	emit SubjectSelect();
}

void SubjectOne::on_btn_delete_clicked() {
	emit SubjectDelete();
}
