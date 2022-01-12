#include "SubjectsUi.h"

void SubjectsUi::DelSubject(SubjectOne* question_ptr) {
	std::string subj_name = question_ptr->Name().toStdString();
	this->setFixedHeight(height() - question_ptr->height());
	_layout->removeWidget(question_ptr);
	question_ptr->hide();
	delete (question_ptr);
	JsonMath::instance()->DelSubject(subj_name);
}

void SubjectsUi::AddSubject(const QString& name) {
	SubjectOne* subject_ptr = new SubjectOne(name, this ,_have_delete);
	connect(subject_ptr, &SubjectOne::SubjectDelete, this, [=]() {
		DelSubject(subject_ptr);
		});
	connect(subject_ptr, &SubjectOne::SubjectSelect, this ,[=]() {
		emit SubjectSelect(subject_ptr->Name());
		});
	_layout->addWidget(subject_ptr);
	this->setFixedHeight(height() + subject_ptr->height());
}

SubjectsUi::SubjectsUi(QWidget *parent)
	: QWidget(parent), _layout(new QVBoxLayout), _have_delete(true)
{
	setLayout(_layout);
	_layout->setMargin(0);
	_layout->setSpacing(0);
}

SubjectsUi::~SubjectsUi()
{
	delete _layout;
}

void SubjectsUi::ClearAll() {
	QList<SubjectOne*> subjects = findChildren<SubjectOne*>();
	for (QList<SubjectOne*>::const_iterator itr = subjects.cbegin(); itr != subjects.cend(); ++itr) {
		this->setFixedHeight(height() - (*itr)->height());
		_layout->removeWidget((*itr));
		(*itr)->hide();
		delete (*itr);
	}
}

void SubjectsUi::NoDelete() {
	_have_delete = false;
}
