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
};



#endif