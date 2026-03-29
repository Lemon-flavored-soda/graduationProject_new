//
// Created by 86157 on 2026/3/27.
//

#ifndef CLIENT_CHAT_DIALOG_H
#define CLIENT_CHAT_DIALOG_H

#include <QDialog>
#include "global.h"


QT_BEGIN_NAMESPACE
namespace Ui { class ChatDialog; }
QT_END_NAMESPACE

class ChatDialog : public QDialog {
Q_OBJECT

public:
    explicit ChatDialog(QWidget *parent = nullptr);

    ~ChatDialog() override;

private:
    void ShowSearch(bool bsearch = false);
    Ui::ChatDialog *ui;
    ChatUIMode _mode;
    ChatUIMode _state;
};


#endif //CLIENT_CHAT_DIALOG_H
