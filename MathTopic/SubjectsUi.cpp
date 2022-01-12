#include "SubjectsUi.h"
extern std::string MathSubjectsPath;
void SubjectsUi::DelSubject(SubjectOne* question_ptr) {
	std::string subj_name = question_ptr->Name().toStdString();
	this->setFixedHeight(height() - question_ptr->height());
	_layout->removeWidget(question_ptr);
	question_ptr->hide();
	delete (question_ptr);
	std::ifstream file;
	file.open(MathSubjectsPath, std::ios::in);
	if (!file.is_open()) {
		return;
	}
	nlohmann::json js;
	file >> js;
	file.close();
	nlohmann::json::iterator find = js.find("MathSubjects");
	if (find != js.cend()) {
		nlohmann::json::iterator find_sub = find->find(subj_name);
		if (find_sub != find->cend()) {
			find->erase(find_sub);
		}
	}
	std::fstream file_out;
	file_out.open(MathSubjectsPath, std::ios::out);
	if (!file_out.is_open()) {
		return;
	}
	file_out << std::setw(4) << js << std::endl;
	file_out.close();
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
