//
// Created by 86157 on 2026/3/30.
//

#include "ListItemBase.h"
#include <QStyleOption>
#include <QPainter>

ListItemBase::ListItemBase(QWidget *parent) {

}

void ListItemBase::SetItemType(ListItemType itemType) {
    _itemType = itemType;
}

ListItemType ListItemBase::GetItemType() {
    return _itemType;
}

void ListItemBase::paintEvent(QPaintEvent *event) {
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget,&opt,&p,this);
    QWidget::paintEvent(event);
}
