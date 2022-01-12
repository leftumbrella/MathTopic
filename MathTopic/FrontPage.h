#pragma once

#include <QWidget>
#include <QPainter>
#include <QtMath>
#include <QPaintEvent>
#include "FunctionCore.h"
#include "ui_FrontPage.h"
#ifdef Q_OS_WIN
#include <windows.h>
#include <windowsx.h>
#endif
class FrontPage : public QWidget
{
	Q_OBJECT

public:
	FrontPage(QWidget *parent = Q_NULLPTR);
	~FrontPage();
private slots:
	void ShowTrain();
	void Start(int type);
	void LoadSubject(const QString& sub_name);
	void Home();
	void SubjectListPage();
private:
	bool nativeEvent(const QByteArray& eventType, void* message, long* result) override;
	void paintEvent(QPaintEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* e) override;
	void mouseMoveEvent(QMouseEvent* e) override;
	void keyPressEvent(QKeyEvent* event) override;
private:
	Ui::FrontPage ui;
	int _bouderWidth;
	QPoint _click_pos;
};
