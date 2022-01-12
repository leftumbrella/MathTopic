#pragma once

#include <QWidget>
#include <QIcon>
#include <QKeyEvent>
#include "MathAddQuestion.h"
#include <Json/json.hpp>
#include <fstream>
#include <utility>
#include "FunctionCore.h"
#include <random>
#include "ConfigCore.h"
#include <qtmaterialfab.h>
#include <qtmaterialdialog.h>
#include "qtmaterialsnackbar.h"
#include "ui_MathUi.h"

class MathUi : public QWidget
{
	Q_OBJECT
private:
	enum CalType {
		Addition = 1,       // 加法
		Subtraction,        // 减法
		Multiplication,     // 乘法
		Division            // 除法
	};
	enum Model {
		Random ,Subject
	};

private:
	void keyPressEvent(QKeyEvent* event) override;
	void showEvent(QShowEvent* event) override;
public:
	MathUi(QWidget *parent = Q_NULLPTR);
	~MathUi();
	void load(const QString& name);

signals:
	void GoWelcome();
	void MathOver(const QString& sub_name ,int ok_num ,int error_num ,std::time_t time);

private slots:
	void HideKey();
	void on_btn_next_clicked();
	void on_btn_commit_clicked();
private:
	void Commit();
	void Next(bool system_skip = false);
	void Initialize();

	void StatisticsUseTime();
	void StatisticsPlusNum(bool is_ok);

	int RadomNumber(int min, int max);
	bool HaveLess(CalType cal_type);
	int GetMax(CalType cal_type);

	void JudgeOperator();
	int JudgeLeft(CalType cal_type);
	int JudgeRight(CalType cal_type, int left_num);

	bool IsRealAnswer(int& answer_);

private:
	FORMULA Str2Formula(const std::string& str);
	void Reset();
private:
	Ui::MathUi ui;
	QtMaterialFloatingActionButton* _btn_home_ptr;
	QtMaterialFloatingActionButton* _btn_close_ptr;
	QtMaterialDialog* _home_dialog_ptr;
	QtMaterialDialog* _close_dialog_ptr;
	QtMaterialSnackbar* _snackbar;

	int _ok_num;
	int _error_num;
	std::time_t _subject_start_time;

	CalType _cal_type;  // 当前算术类型
	Model _model;

	int _left_num;
	int _right_num;

	bool _is_commited;

	std::time_t _start_time;
	std::size_t _question_num;

	std::vector<std::pair<FORMULA, int> > _formulas;
	QString _sub_name;
	//std::vector<FORMULA> _formulas;
};
