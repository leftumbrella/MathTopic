#pragma once

#include <QWidget>
#include "FunctionCore.h"
#include <qtmaterialfab.h>
#include "ConfigCore.h"
#include "ui_SettingUi.h"

class SettingUi : public QWidget
{
	Q_OBJECT

signals:
	void GoWelcome();

public:
	SettingUi(QWidget *parent = Q_NULLPTR);
	~SettingUi();

private:
	void showEvent(QShowEvent* event) override;

private slots:
	void SoundChanged(bool is_open);
	void CommitSkipChanged(bool is_open);
	void ErrorSkipChanged(bool is_open);
	void KeyDialogChanged(bool is_open);
private:
	Ui::SettingUi ui;
	QtMaterialFloatingActionButton* _btn_home_ptr;
};
