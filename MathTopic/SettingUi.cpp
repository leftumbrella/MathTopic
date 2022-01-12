#include "SettingUi.h"

SettingUi::SettingUi(QWidget *parent)
	: QWidget(parent)
	, _btn_home_ptr(new QtMaterialFloatingActionButton(QIcon(":/MathTopic/home.png"), this))
{
	ui.setupUi(this);

	_btn_home_ptr->setCorner(Qt::TopLeftCorner);
	_btn_home_ptr->setBackgroundColor("#168570");

	connect(_btn_home_ptr, &QtMaterialFloatingActionButton::clicked, this, [=]() {
		QPlaySound(3);
		emit GoWelcome();
		});

	ui.TG_commit_skip->setActiveColor("#1E2AD2");
	ui.TG_error_skip->setActiveColor("#1E2AD2");
	ui.TG_key_dialog->setActiveColor("#1E2AD2");
	ui.TG_sound->setActiveColor("#1E2AD2");

	connect(ui.TG_sound, &QtMaterialToggle::toggled, this, &SettingUi::SoundChanged);
	connect(ui.TG_commit_skip, &QtMaterialToggle::toggled, this, &SettingUi::CommitSkipChanged);
	connect(ui.TG_error_skip, &QtMaterialToggle::toggled, this, &SettingUi::ErrorSkipChanged);
	connect(ui.TG_key_dialog, &QtMaterialToggle::toggled, this, &SettingUi::KeyDialogChanged);

	_btn_home_ptr->setToolTip(QStringLiteral("ึ๗าณ"));
}

SettingUi::~SettingUi()
{
}

void SettingUi::showEvent(QShowEvent* event) {
	QWidget::showEvent(event);
	ui.TG_commit_skip->setChecked(ConfigCore::instance()->ReadValue("BaseSetting", "CommitSkip", nullptr) == "true");
	ui.TG_error_skip->setChecked(ConfigCore::instance()->ReadValue("BaseSetting", "ErrorSkip", nullptr) == "true");
	ui.TG_key_dialog->setChecked(ConfigCore::instance()->ReadValue("BaseSetting", "KeyDialog", nullptr) == "true");
	ui.TG_sound->setChecked(ConfigCore::instance()->ReadValue("BaseSetting", "Sound", nullptr) == "true");
}

void SettingUi::SoundChanged(bool is_open) {
	if (is_open) {
		QSound::play(":/MathTopic/push.wav");
	}
	ConfigCore::instance()->SetValue(is_open, "BaseSetting", "Sound", nullptr);
}

void SettingUi::CommitSkipChanged(bool is_open) {
	QPlaySound(3);
	ConfigCore::instance()->SetValue(is_open, "BaseSetting", "CommitSkip", nullptr);
}

void SettingUi::ErrorSkipChanged(bool is_open) {
	QPlaySound(3);
	ConfigCore::instance()->SetValue(is_open, "BaseSetting", "ErrorSkip", nullptr);
}

void SettingUi::KeyDialogChanged(bool is_open) {
	QPlaySound(3);
	ConfigCore::instance()->SetValue(is_open, "BaseSetting", "KeyDialog", nullptr);
}
