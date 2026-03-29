//
// Created by 86157 on 2026/3/25.
//

#include "ClickedLabel.h"
#include <QMouseEvent>
ClickedLabel::ClickedLabel(QWidget* parent):QLabel (parent)
{
    QPixmap pixmap(":/image/隐藏密码.png");
    this->setPixmap(pixmap.scaled(20, 20, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void ClickedLabel::enterEvent(QEnterEvent *event) {
    //设置图标加缩放
    QPixmap pixmap(":/image/隐藏密码1.png");
    this->setPixmap(pixmap.scaled(20, 20, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    setCursor(Qt::PointingHandCursor);
}

void ClickedLabel::leaveEvent(QEvent *event) {
    QPixmap pixmap(":/image/隐藏密码.png");
    this->setPixmap(pixmap.scaled(20, 20, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    setCursor(Qt::ArrowCursor);
}

void ClickedLabel::mousePressEvent(QMouseEvent *ev) {
    QPixmap pixmap(":/image/显示密码.png");
    this->setPixmap(pixmap.scaled(20, 20, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    QLabel::mousePressEvent(ev);
    emit clicked();
}

void ClickedLabel::mouseReleaseEvent(QMouseEvent *ev) {
    QPixmap pixmap(":/image/隐藏密码.png");
    this->setPixmap(pixmap.scaled(20, 20, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    QLabel::mouseReleaseEvent(ev);
    emit release();
}

