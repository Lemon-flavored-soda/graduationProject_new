//
// Created by 86157 on 2026/4/1.
//

// You may need to build the project (run Qt uic code generator) to get "ui_AddUserItem.h" resolved

#include "adduseritem.h"
#include "ui_AddUserItem.h"


AddUserItem::AddUserItem(QWidget *parent) :
        ListItemBase(parent), ui(new Ui::AddUserItem) {
    ui->setupUi(this);
    SetItemType(ListItemType::ADD_USER_TIP_ITEM);
}

AddUserItem::~AddUserItem() {
    delete ui;
}

QSize AddUserItem::sizeHint() const {
    return QSize(224,70);
}
