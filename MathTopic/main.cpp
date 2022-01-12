#include "FrontPage.h"
#include "ConfigCore.h"
#include <QtWidgets/QApplication>
#include <QStandardPaths>
#include <boost/filesystem.hpp>
#include <Json/json.hpp>

std::string MathSubjectsPath;
QMediaPlayer* G_Player_ptr = nullptr;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	G_Player_ptr = new QMediaPlayer;

	//设置QToolTip颜色
	QPalette palette = QToolTip::palette();
	palette.setColor(QPalette::Inactive, QPalette::ToolTipBase, Qt::white);   //设置ToolTip背景色
	palette.setColor(QPalette::Inactive, QPalette::ToolTipText, Qt::black);    //设置ToolTip字体色
	QToolTip::setPalette(palette);
	QFont font;
	QStringList familys;
	familys << "Consolas" << QStringLiteral("楷体");
	font.setPointSize(15);
	font.setFamilies(familys);
	QToolTip::setFont(font);

	std::string config_path = "./"/*QCoreApplication::applicationDirPath().toStdString()*/;
	config_path += "/MathTopicConfigure";
    MathSubjectsPath = config_path + "/MathSubjects.json";
	ConfigCore::instance()->SetPath(config_path);

    {
        if (!boost::filesystem::is_regular_file(MathSubjectsPath)) {
			std::fstream file;
			if (!boost::filesystem::is_regular_file(MathSubjectsPath)) {
				file.open(MathSubjectsPath, std::ios::out);
				if (file.is_open()) {
					file.close();
				}
				nlohmann::json js;
				js["MathSubjects"][QStringLiteral("默认科目").toStdString()].push_back("1+1=2");
				js["MathSubjects"][QStringLiteral("默认科目").toStdString()].push_back("2+2=4");
				js["MathSubjects"][QStringLiteral("默认科目").toStdString()].push_back("3+3=6");
				js["MathSubjects"][QStringLiteral("默认科目").toStdString()].push_back("4+4=8");
				js["MathSubjects"][QStringLiteral("默认科目").toStdString()].push_back("5+5=10");
				std::fstream file_out;
				file_out.open(MathSubjectsPath, std::ios::out);
				if (file_out.is_open()) {
					file_out << std::setw(4) << js << std::endl;
					file_out.close();
				}
			}
        }
		if (ConfigCore::instance()->ReadValue("BaseSetting", "CommitSkip", nullptr).empty()) {
			ConfigCore::instance()->SetValue(true, "BaseSetting", "Sound", nullptr);
			ConfigCore::instance()->SetValue(false, "BaseSetting", "CommitSkip", nullptr);
			ConfigCore::instance()->SetValue(false, "BaseSetting", "ErrorSkip", nullptr);
			ConfigCore::instance()->SetValue(true, "BaseSetting", "KeyDialog", nullptr);
		}
    }




    FrontPage w;
    w.show();
    return a.exec();
}
