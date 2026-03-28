//
// Created by 86157 on 2026/3/25.
//

#ifndef CLIENT_CLICKEDLABEL_H
#define CLIENT_CLICKEDLABEL_H
#include <QLabel>
#include "global.h"

class ClickedLabel : public QLabel{
    Q_OBJECT
public:
    ClickedLabel(QWidget* parent = nullptr);
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *ev) override;
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;

signals:
    void clicked();
    void release();
};


#endif //CLIENT_CLICKEDLABEL_H
