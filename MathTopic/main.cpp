#include "FrontPage.h"
#include <QtWidgets/QApplication>
#include <QStandardPaths>
#include "JsonMath.h"
#include "ConfigCore.h"

QMediaPlayer* G_Player_ptr = nullptr;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	G_Player_ptr = new QMediaPlayer;

	//����QToolTip��ɫ
	QPalette palette = QToolTip::palette();
	palette.setColor(QPalette::Inactive, QPalette::ToolTipBase, Qt::white);   //����ToolTip����ɫ
	palette.setColor(QPalette::Inactive, QPalette::ToolTipText, Qt::black);    //����ToolTip����ɫ
	QToolTip::setPalette(palette);
	QFont font;
	QStringList familys;
	familys << "Consolas" << QStringLiteral("����");
	font.setPointSize(15);
	font.setFamilies(familys);
	QToolTip::setFont(font);

	std::string config_path = "."/*QCoreApplication::applicationDirPath().toStdString()*/;
	config_path += "/MathTopicConfigure/";
	
	std::string setting_file = config_path + "config.json";
	ConfigCore::instance()->SetPath(setting_file);
	std::string math_sub_file = config_path + "MathSubjects.json";
	JsonMath::instance()->SetFile(math_sub_file);
	
	if (std::filesystem::is_empty(math_sub_file)) {

		std::vector<std::string> formulas{
		"1+1=2","2+2=4","4+4=8","5+5=10"
		};
		JsonMath::instance()->WriteFormulas(formulas, QStringLiteral("Ĭ�Ͽ�Ŀ").toStdString());
	}	

	if (std::filesystem::is_empty(setting_file)) {
		ConfigCore::instance()->SetValue(true, "BaseSetting", "Sound", nullptr);
		ConfigCore::instance()->SetValue(false, "BaseSetting", "CommitSkip", nullptr);
		ConfigCore::instance()->SetValue(false, "BaseSetting", "ErrorSkip", nullptr);
		ConfigCore::instance()->SetValue(true, "BaseSetting", "KeyDialog", nullptr);
	}


    FrontPage w;
    w.show();
    return a.exec();
}
