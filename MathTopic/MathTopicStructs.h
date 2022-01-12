#ifndef MATHTOPIC_MATHTOPICSTRUCTS_H_
#define MATHTOPIC_MATHTOPICSTRUCTS_H_

#include "MathTopicDefines.h"

// 数学算式
struct FORMULA {
	int left;	// 左运算数
	int oper;	// 运算符号 "1:+" "2:-" "3:*" "4:/"
	int right;	// 右运算数
	int answer;	// 答案
	FORMULA() :left(0), oper(1), right(0), answer(0) {

	}
	FORMULA(int left_,int oper_ ,int right_ ,int answer_) :left(left_), oper(oper_), right(right_), answer(answer_) {

	}
};



#endif