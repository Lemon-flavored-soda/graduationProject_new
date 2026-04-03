//
// Created by 86157 on 2026/4/1.
//

#include "ClickedOnceLabel.h"
ClickedOnceLabel::ClickedOnceLabel(QWidget* parent):QLabel(parent){
    setCursor(Qt::PointingHandCursor);
}

void ClickedOnceLabel::mouseReleaseEvent(QMouseEvent *ev) {
    if(ev->button() == Qt::LeftButton){
        emit clicked(this->text());
        return;
    }
    //调用基类的mousePressEvent以保证正常的事件处理
    QLabel::mouseReleaseEvent(ev);
}
