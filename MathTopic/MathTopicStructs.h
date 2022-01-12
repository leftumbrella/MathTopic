#ifndef MATHTOPIC_MATHTOPICSTRUCTS_H_
#define MATHTOPIC_MATHTOPICSTRUCTS_H_

#include "MathTopicDefines.h"

// ��ѧ��ʽ
struct FORMULA {
	int left;	// ��������
	int oper;	// ������� "1:+" "2:-" "3:*" "4:/"
	int right;	// ��������
	int answer;	// ��
	FORMULA() :left(0), oper(1), right(0), answer(0) {

	}
	FORMULA(int left_,int oper_ ,int right_ ,int answer_) :left(left_), oper(oper_), right(right_), answer(answer_) {

	}
};



#endif