//
// Created by 86157 on 2026/3/31.
//

#ifndef CLIENT_CHATITEMBASE_H
#define CLIENT_CHATITEMBASE_H
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include "global.h"

class BubbleFram{

};

class ChatItemBase:public QWidget {
    Q_OBJECT
public:
    explicit ChatItemBase(ChatRole role, QWidget *parent = nullptr);
    void setUserName(const QString &name);
    void setUserIcon(const QPixmap &icon);
    void setWidget(QWidget *w);

private:
    ChatRole m_role;
    QLabel *m_pNameLabel;
    QLabel *m_pIconLabel;
    QWidget *m_pBubble;
};


#endif //CLIENT_CHATITEMBASE_H
