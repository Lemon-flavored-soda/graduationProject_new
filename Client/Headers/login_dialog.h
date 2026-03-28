//
// Created by 86157 on 2026/3/19.
//

#ifndef CLIENT_LOGIN_DIALOG_H
#define CLIENT_LOGIN_DIALOG_H

#include <QDialog>
#include "register_dialog.h"


QT_BEGIN_NAMESPACE
namespace Ui { class LoginDialog; }
QT_END_NAMESPACE

class LoginDialog : public QDialog {
Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);

    ~LoginDialog() override;

signals:
    void sig_connect_tcp(ServerInfo);

private slots:
    void on_btn_login_clicked();
    void slot_login_mod_finish(ReqId id, QString res, ErrorCodes err);
    void slot_tcp_con_finish(bool bsuccess);
    void slot_login_failed(int);

protected:
    bool eventFilter(QObject *, QEvent *) override;

private:
    Ui::LoginDialog *ui;
    RegisterDialog* rg_dialog;
    bool checkUserValid();
    bool checkPwdValid();
    void initHttpHandlers();
    QMap<ReqId, std::function<void(const QJsonObject&)>> _handlers;
    int _uid;
    QString _token;
};


#endif //CLIENT_LOGIN_DIALOG_H
