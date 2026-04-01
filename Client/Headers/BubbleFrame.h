//
// Created by 86157 on 2026/3/31.
//

#ifndef CLIENT_BUBBLEFRAME_H
#define CLIENT_BUBBLEFRAME_H


#include <QFrame>
#include "global.h"
#include <QHBoxLayout>
class BubbleFrame : public QFrame
{
Q_OBJECT
public:
    BubbleFrame(ChatRole role, QWidget *parent = nullptr);
    void setWidget(QWidget *w);
protected:
    //绘制气泡
    void paintEvent(QPaintEvent *e);
private:
    QHBoxLayout *m_pHLayout;
    ChatRole m_role;
    int      m_margin;
};

#endif //CLIENT_BUBBLEFRAME_H
