#include <QApplication>
#include "Headers/login_dialog.h"
#include "Headers/register_dialog.h"
#include "Headers/chat_dialog.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QFile file(":/stylesheet.qss"); // 对应前缀为 "/" 的情况
    if (file.open(QFile::ReadOnly)) {
        QString styleSheet = QString::fromUtf8(file.readAll());
        a.setStyleSheet(styleSheet);
    }
    QString  fileName = "config.ini";
    QString app_path = QCoreApplication::applicationDirPath();
    QString config_path =  QDir::toNativeSeparators(app_path + QDir::separator() + fileName);
    QSettings settings(config_path, QSettings::IniFormat);
    QString gate_host = settings.value("GateServer/host").toString();
    QString gate_port = settings.value("GateServer/port").toString();
    gate_url_prefix = "http://" + gate_host + ":" + gate_port;

//    LoginDialog win;
    ChatDialog win;
    win.show();
    return QApplication::exec();
}
