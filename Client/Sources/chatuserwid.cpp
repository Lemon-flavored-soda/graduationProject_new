//
// Created by 86157 on 2026/3/29.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ChatUserWid.h" resolved

#include "chatuserwid.h"
#include "ui_ChatUserWid.h"


ChatUserWid::ChatUserWid(QWidget *parent) :
        ListItemBase(parent), ui(new Ui::ChatUserWid) {
    ui->setupUi(this);
    SetItemType(ListItemType::CHAT_USER_ITEM);
}

ChatUserWid::~ChatUserWid() {
    delete ui;
}

void ChatUserWid::SetInfo(QString name, QString head, QString msg) {
    _name = name;
    _head = head;
    _msg = msg;
    //加载图片
    QPixmap pixmap(_head);
    //设置图片自动缩放
    ui->icon_lb->setPixmap(pixmap.scaled(ui->icon_lb->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
    //缩放label的内容
    ui->icon_lb->setScaledContents(true);
    ui->user_name_lb->setText(_name);
    ui->user_chat_lb->setText(_msg);

}

QSize ChatUserWid::sizeHint() const {
    return QSize(224,70);//返回自定义的尺寸
}

