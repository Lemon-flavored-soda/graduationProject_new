//
// Created by 86157 on 2026/3/29.
//

#ifndef CLIENT_CHATUSERLIST_H
#define CLIENT_CHATUSERLIST_H
#include <QListWidget>
#include <QEvent>
#include <QScrollBar>
#include <QDebug>
#include <QWheelEvent>

class ChatUserList :public QListWidget{
    Q_OBJECT
public:
    ChatUserList(QWidget* parent = nullptr);
    ~ChatUserList();
protected:
    bool eventFilter(QObject *object, QEvent *event) override;
signals:
    void sig_loading_chat_user();
};


#endif //CLIENT_CHATUSERLIST_H
