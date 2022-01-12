#pragma once

#include <QWidget>
#include <fstream>
#include <Json/json.hpp>
#include <iomanip>
#include <sstream>
#include <QToolTip>
#include <QKeyEvent>
#include <QShowEvent>

#include <qtmaterialfab.h>
#include <QLabel>
#include <qtmaterialdialog.h>
#include <boost/lexical_cast.hpp>
#include "FunctionCore.h"
#include "ui_MathTopicConf.h"

class MathTopicConf : public QWidget
{
	Q_OBJECT

signals:
	void GoSelectSubject();
	void GoHome();

public:
	MathTopicConf(QWidget *parent = Q_NULLPTR);
	~MathTopicConf();
	bool load(const QString& sub_name);
private:
	void showEvent(QShowEvent* event) override;
	void keyPressEvent(QKeyEvent* event) override;

private:
	void Push(int push_what);
	void OverPush();
	void ClearPush();

private slots:
	void on_btn_finish_clicked();
	void on_CB_fast_toggled(bool);
	void on_CB_auto_answer_toggled(bool);
private:
	void AddFormula(const std::string& formula_str);
	int SaveFormulas(bool is_override = false);
	std::string Formula2Str(const FORMULA& formula);
private:
	Ui::MathTopicConf ui;
	QtMaterialFloatingActionButton* _btn_close_ptr;
	QtMaterialFloatingActionButton* _btn_home_ptr;

	QtMaterialDialog* _close_dialog_ptr;
	QtMaterialDialog* _info_dialog_ptr;
	QtMaterialDialog* _override_ptr;

	bool _is_editing;

	int _left_num;
	int _oper_num;
	bool _have_oper;
	int _right_num;
};
