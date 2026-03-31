//
// Created by 86157 on 2026/3/30.
//

#ifndef CLIENT_CHATPAGE_H
#define CLIENT_CHATPAGE_H

#include <QWidget>
#include "userdata.h"
#include <QMap>


QT_BEGIN_NAMESPACE
namespace Ui { class ChatPage; }
QT_END_NAMESPACE

class ChatPage : public QWidget {
Q_OBJECT

public:
    explicit ChatPage(QWidget *parent = nullptr);

    ~ChatPage() override;
    void SetUserInfo(std::shared_ptr<UserInfo> user_info);
    void AppendChatMsg(std::shared_ptr<TextChatData> msg);
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    Ui::ChatPage *ui;
    void clearItems();
    std::shared_ptr<UserInfo> _user_info;
    QMap<QString, QWidget*>  _bubble_map;

public slots:
    void on_send_btn_clicked();
    void on_receive_btn_clicked();
signals:
    void sig_append_send_chat_msg(std::shared_ptr<TextChatData> msg);
};


#endif //CLIENT_CHATPAGE_H
