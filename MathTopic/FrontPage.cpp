#include "FrontPage.h"
#include "QDesktopWidget"

FrontPage::FrontPage(QWidget *parent)
	: QWidget(parent), _bouderWidth(9)
{
	ui.setupUi(this);

	setWindowFlag(Qt::FramelessWindowHint);
	QDesktopWidget* desktopWidget = QApplication::desktop();
	QRect clientRect = desktopWidget->availableGeometry();
	resize(clientRect.width() / 2, clientRect.height() / 3 * 2);
	setAttribute(Qt::WA_TranslucentBackground);//特别注意这句

	connect(ui.PG_main, &WelcomeUi::GoTrain, this, &FrontPage::ShowTrain);
	connect(ui.PG_Train, &SubjectSelectionUi::GoWelcome, this, &FrontPage::Home);
	connect(ui.PG_Train, &SubjectSelectionUi::Start, this, &FrontPage::Start);
	connect(ui.PG_math, &MathUi::GoWelcome, this, &FrontPage::Home);
	connect(ui.PG_main, &WelcomeUi::GoSetting, this, [=]() {
		ui.stackedWidget->setCurrentWidget(ui.PG_setting);
		});
	connect(ui.PG_setting, &SettingUi::GoWelcome, this, &FrontPage::Home);
	connect(ui.PG_main, &WelcomeUi::GoStatistics, this, [=]() {
		ui.stackedWidget->setCurrentWidget(ui.PG_statistics);
		});
	connect(ui.PG_statistics, &StatisticsUi::GoWelcome, this, &FrontPage::Home);

	connect(ui.PG_main, &WelcomeUi::GoData, this, &FrontPage::SubjectListPage);
	connect(ui.PG_data, &MathTopicConf::GoSelectSubject, this, &FrontPage::SubjectListPage);
	connect(ui.PG_subjectsList, &SubjectList::SubjectSelect, this, &FrontPage::LoadSubject);
	connect(ui.PG_subjectsList, &SubjectList::SubjectNew, this, [=]() {
		ui.stackedWidget->setCurrentWidget(ui.PG_data);
		});
	connect(ui.PG_data, &MathTopicConf::GoHome, this, &FrontPage::Home);
	connect(ui.PG_subjectsList, &SubjectList::GoHome, this, &FrontPage::Home);


	connect(ui.WG_SubjectChoose, &SubjectChooser::GoSubject, this, [=](const QString& sub_name) {
		ui.PG_math->load(sub_name);
		ui.stackedWidget->setCurrentWidget(ui.PG_math);
		});
	connect(ui.PG_math, &MathUi::MathOver, this, [=](const QString& sub_name ,int ok_num, int error_num, std::time_t time) {
		ui.PG_end->ChangeOver(sub_name ,ok_num, error_num, time);
		ui.stackedWidget->setCurrentWidget(ui.PG_end);
		});
	connect(ui.PG_end ,&EndUi::GoHome ,this , &FrontPage::Home);
	connect(ui.PG_end, &EndUi::ReTry, this, [=](const QString& sub_name) {
		ui.PG_math->load(sub_name);
		ui.stackedWidget->setCurrentWidget(ui.PG_math);
		});


	connect(ui.WG_SubjectChoose, &SubjectChooser::GoSetting, this, [=]() {
		ui.stackedWidget->setCurrentWidget(ui.PG_setting);
		});
	connect(ui.WG_SubjectChoose, &SubjectChooser::GoStatistics, this, [=]() {
		ui.stackedWidget->setCurrentWidget(ui.PG_statistics);
		});
	connect(ui.WG_SubjectChoose, &SubjectChooser::GoData, this, &FrontPage::SubjectListPage);

	ui.stackedWidget->setCurrentWidget(ui.WG_SubjectChoose);

	
}

FrontPage::~FrontPage(){

}

void FrontPage::ShowTrain() {
	ui.stackedWidget->setCurrentWidget(ui.PG_Train);
}

void FrontPage::Start(int type) {
	//_btn_close_ptr->setIcon(QIcon(":/MathTopic/home.png"));
	switch (type)
	{
	case 2:	ui.stackedWidget->setCurrentWidget(ui.PG_math);	break;
	default:
		break;
	}
}

void FrontPage::LoadSubject(const QString& sub_name) {
	QPlaySound(3);
	ui.stackedWidget->setCurrentWidget(ui.PG_data);
	ui.PG_data->load(sub_name);
}

void FrontPage::Home() {
	ui.stackedWidget->setCurrentWidget(ui.WG_SubjectChoose);
}

void FrontPage::SubjectListPage() {
	ui.stackedWidget->setCurrentWidget(ui.PG_subjectsList);
}

bool FrontPage::nativeEvent(const QByteArray& eventType, void* message, long* result) {
#ifdef Q_OS_WIN
	MSG* msg = (MSG*)message;
	switch (msg->message) {
	case WM_NCHITTEST:
		int xPos = GET_X_LPARAM(msg->lParam) - this->frameGeometry().x();
		int yPos = GET_Y_LPARAM(msg->lParam) - this->frameGeometry().y();
		int nUseFulWidth = width() - _bouderWidth;
		int nUseFulHeight = height() - _bouderWidth;
		if (xPos < _bouderWidth && yPos < _bouderWidth) {	//左上角
			*result = HTTOPLEFT;
		}
		else if (xPos >= nUseFulWidth && yPos < _bouderWidth) {	//右上角
			*result = HTTOPRIGHT;
		}
		else if (xPos < _bouderWidth && yPos >= nUseFulHeight) {	//左下角
			*result = HTBOTTOMLEFT;
		}
		else if (xPos >= nUseFulWidth && yPos >= nUseFulHeight) {	//右下角
			*result = HTBOTTOMRIGHT;
		}
		else if (xPos < _bouderWidth) {	//左边
			*result = HTLEFT;
		}
		else if (xPos >= nUseFulWidth) {	//右边
			*result = HTRIGHT;
		}
		else if (yPos < _bouderWidth) {	//上边
			*result = HTTOP;
		}
		else if (yPos >= nUseFulHeight) {	//下边
			*result = HTBOTTOM;
		}else {
			return false;
		}
		return true;
	}
#endif
	return QWidget::nativeEvent(eventType, message, result);	//此处返回false，留给其他事件处理器处理
}

void FrontPage::paintEvent(QPaintEvent* event) {
	if (isFullScreen()) {
		QWidget::paintEvent(event);
		return;
	}
	QPainterPath path;
	path.setFillRule(Qt::WindingFill);
	path.addRect(10, 10, this->width() - 20, this->height() - 20);

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.fillPath(path, QBrush(Qt::white));

	QColor color(0, 0, 0, 50);
	for (int i = 0; i < 10; i++) {
		QPainterPath path;
		path.setFillRule(Qt::WindingFill);
		path.addRect(10 - i, 10 - i, this->width() - (10 - i) * 2, this->height() - (10 - i) * 2);
		color.setAlpha(150 - qSqrt(i) * 50);
		painter.setPen(color);
		painter.drawPath(path);
	}
	
	QWidget::paintEvent(event);
}

void FrontPage::mouseReleaseEvent(QMouseEvent* event) {
	_click_pos = QPoint();
}

void FrontPage::mousePressEvent(QMouseEvent* e) {
	if (e->button() == Qt::LeftButton) {
		_click_pos = e->globalPos();
	}
	QWidget::mousePressEvent(e);
}

void FrontPage::mouseMoveEvent(QMouseEvent* e) {
	if (e->buttons() & Qt::LeftButton && _click_pos != QPoint()) {
		if (windowState() != Qt::WindowFullScreen) {
			move(pos() + e->globalPos() - _click_pos);
			_click_pos = e->globalPos();
		}
	}
	QWidget::mouseMoveEvent(e);
}

void FrontPage::keyPressEvent(QKeyEvent* event) {
	switch (event->key()) {
	case Qt::Key_F11:
		showFullScreen();
		layout()->setMargin(0);
		break;
	case Qt::Key_Escape:
		showNormal();
		layout()->setMargin(9);
		break;
	}
	QWidget::keyPressEvent(event);
}
