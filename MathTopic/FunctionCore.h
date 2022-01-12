#pragma once

#include <QSound>
#include <QMediaPlayer>
#include "ConfigCore.h"
extern QMediaPlayer* G_Player_ptr;
static void QPlaySound(int type) {
	if (ConfigCore::instance()->ReadValue("BaseSetting", "Sound", nullptr) == "false") {
		return;
	}
	switch (type)
	{
	case 1: {
		G_Player_ptr->setMedia(QUrl::fromLocalFile(QStringLiteral("./MathTopicConfigure/ÕýÈ·.mp3")));
		G_Player_ptr->play();
		break;
	}
	case 2: {
		G_Player_ptr->setMedia(QUrl::fromLocalFile(QStringLiteral("./MathTopicConfigure/´íÎó.mp3")));
		G_Player_ptr->play();
		break;
	}
	case 3:	QSound::play(":/MathTopic/push.wav");	break;
	case 4:	QSound::play(":/MathTopic/message.wav");	break;
	}
}