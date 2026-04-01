//
// Created by 86157 on 2026/4/1.
//

#ifndef CLIENT_ADDUSERITEM_H
#define CLIENT_ADDUSERITEM_H

#include <QWidget>
#include "ListItemBase.h"


QT_BEGIN_NAMESPACE
namespace Ui { class AddUserItem; }
QT_END_NAMESPACE

class AddUserItem : public ListItemBase {
Q_OBJECT

public:
    explicit AddUserItem(QWidget *parent = nullptr);

    ~AddUserItem() override;
    QSize sizeHint() const override;
private:
    Ui::AddUserItem *ui;
};


#endif //CLIENT_ADDUSERITEM_H
