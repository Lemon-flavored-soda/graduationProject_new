//
// Created by 86157 on 2026/3/20.
//

#ifndef CLIENT_REGISTER_DIALOG_H
#define CLIENT_REGISTER_DIALOG_H

#include <QWidget>
#include "global.h"
#include <QMap>

QT_BEGIN_NAMESPACE
namespace Ui { class RegisterDialog; }
QT_END_NAMESPACE

class RegisterDialog : public QWidget {
Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = nullptr);

    ~RegisterDialog() override;

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

public slots:
    void on_register_now_clicked();

private slots:
    void slot_reg_mod_finish(ReqId id, QString res, ErrorCodes err);
private:
    bool checkUserValid();
    bool checkEmailValid();
    bool checkPassValid();
    bool checkVarifyValid();
    void initHttpHandlers();
    QMap<ReqId, std::function<void(const QJsonObject&)>> handlers;
    Ui::RegisterDialog *ui;
    bool flag[4];
};


#endif //CLIENT_REGISTER_DIALOG_H
