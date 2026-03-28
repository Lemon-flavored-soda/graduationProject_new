//
// Created by 86157 on 2026/3/20.
//

#ifndef CLIENT_TOAST_H
#define CLIENT_TOAST_H

//错误提示小图标

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>
#include <QTimer>

class Toast : public QWidget {
Q_OBJECT
public:
    explicit Toast(QWidget *parent = nullptr);

    // 静态方便函数：直接调用即可显示
    static void showMessage(QWidget *parent, const QString &message, int duration = 3000);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QLabel *m_label;
    QTimer *m_timer;
    QPropertyAnimation *m_fadeIn;
    QPropertyAnimation *m_fadeOut;
};

#endif //CLIENT_TOAST_H
