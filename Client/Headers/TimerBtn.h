//
// Created by 86157 on 2026/3/25.
//

#ifndef CLIENT_TIMERBTN_H
#define CLIENT_TIMERBTN_H
#include <QLabel>
#include <QTimer>

class TimerBtn : public QLabel
{
public:
    TimerBtn(QWidget *parent = nullptr);
    ~ TimerBtn();

    // 重写mouseReleaseEvent
    virtual void mouseReleaseEvent(QMouseEvent *e) override;
private:
    QTimer  *_timer;
    int _counter;
};

#endif //CLIENT_TIMERBTN_H
