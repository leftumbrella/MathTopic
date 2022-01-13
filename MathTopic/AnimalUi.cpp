#include "AnimalUi.h"

AnimalUi::AnimalUi(QWidget *parent)
	: QWidget(parent)
	,_2R_row_style("border-image:url(\":/Resources/image/cow_2right.png\")")
	,_2L_row_style("border-image:url(\":/Resources/image/cow_2left.png\")")
	, _2R_rbt_style("border-image:url(\":/Resources/image/rabbit.png\")")
	, _2L_rbt_style("border-image:url(\":/Resources/image/rabbit_2right.png\")")
{
	ui.setupUi(this);
	
}

AnimalUi::~AnimalUi()
{
}

bool AnimalUi::setAnimal(int left, int oper, int right) {
	if (left > 10 || right > 10) {
		return false;
	}
	int anser = 0;
	int l_animal = 0, r_animal = 0;
	switch (oper) {
		case 1:
			anser = left + right;
			l_animal = left;
			r_animal = right;
			
			break;
		case 2:
			anser = left - right;
			r_animal = right;
			l_animal = anser;
			break;
		default: return false;
	}



	for (int i = 1; i <= 10; ++i) {
		QString obj_name = QString("LBA_%1").arg(i);
		
		QLabel* label_ptr = findChild<QLabel*>(obj_name);
		if (label_ptr != nullptr) {
			if (i <= l_animal) {
				QString style = oper == 1 ? _2R_row_style : _2R_rbt_style;
				label_ptr->show();
				label_ptr->setStyleSheet(style);
			} else {
				label_ptr->hide();
			}
		}
	}

	for (int i = 1; i <= 10; ++i) {
		QString obj_name = QString("RBA_%1").arg(i);
		
		QLabel* label_ptr = findChild<QLabel*>(obj_name);
		if (label_ptr != nullptr) {
			if (i <= r_animal) {
				QString style = oper == 1 ? _2L_row_style : _2L_rbt_style;
				label_ptr->show();
				label_ptr->setStyleSheet(style);
			} else {
				label_ptr->hide();
			}
		}
	}
	return true;
}
