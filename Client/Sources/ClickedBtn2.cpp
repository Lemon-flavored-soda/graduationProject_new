//
// Created by 86157 on 2026/3/30.
//

#include "ClickedBtn2.h"
#include <QVariant>
#include "global.h"
#include <QKeyEvent>

ClickedBtn2::ClickedBtn2(QWidget *parent):QPushButton (parent)
{
    setCursor(Qt::PointingHandCursor); // 设置光标为小手
    //保证调用的时候不会触发回车事件
    setFocusPolicy(Qt::NoFocus);
}

ClickedBtn2::~ClickedBtn2(){

}


void ClickedBtn2::SetState(QString normal, QString hover, QString press)
{
    _hover = hover;
    _normal = normal;
    _press = press;
    setProperty("state",normal);
    repolish(this);
    update();
}
void ClickedBtn2::enterEvent(QEnterEvent *event) {
    setProperty("state",_hover);
    repolish(this);
    update();
    QPushButton::enterEvent(event);
}

void ClickedBtn2::leaveEvent(QEvent *event)
{
    setProperty("state",_normal);
    repolish(this);
    update();
    QPushButton::leaveEvent(event);
}

void ClickedBtn2::mousePressEvent(QMouseEvent *event)
{
    setProperty("state",_press);
    repolish(this);
    update();
    QPushButton::mousePressEvent(event);
}

void ClickedBtn2::mouseReleaseEvent(QMouseEvent *event)
{
    setProperty("state",_hover);
    repolish(this);
    update();
    QPushButton::mouseReleaseEvent(event);
}

