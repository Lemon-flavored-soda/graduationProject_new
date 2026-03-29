//
// Created by 86157 on 2026/3/29.
//

#include "CustomizeEdit.h"

void CustomizeEdit::focusOutEvent(QFocusEvent *event) {
    //调用基类的focusOutEvent()方法，保证基类的行为得到执行
    QLineEdit::focusOutEvent(event);
    //发送失去焦点的信号
    emit sig_focus_out();
}

CustomizeEdit::CustomizeEdit(QWidget *parent) : QLineEdit(parent) ,_max_len(0){
    connect(this,&QLineEdit::textChanged,this,&CustomizeEdit::limitTextLength);

}

void CustomizeEdit::SetMaxLength(int maxLen) {
    _max_len = maxLen;
}

void CustomizeEdit::limitTextLength(QString text) {

    if(_max_len <= 0){
        return;
    }
    QByteArray byteArray = text.toUtf8();
    //判断现在的字节数组是否大于所限制的长度
    if(byteArray.size() > _max_len){
        //截取
        byteArray = byteArray.left(_max_len);
        this->setText(QString::fromUtf8(byteArray));
    }
}
