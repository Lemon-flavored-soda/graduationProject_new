//
// Created by 86157 on 2026/4/2.
//

#ifndef CLIENT_GROUPTIPITEM_H
#define CLIENT_GROUPTIPITEM_H

#include <QWidget>
#include "ListItemBase.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GroupTipItem; }
QT_END_NAMESPACE

class GroupTipItem : public ListItemBase {
Q_OBJECT

public:
    explicit GroupTipItem(QWidget *parent = nullptr);
    ~GroupTipItem() override;
    QSize sizeHint() const override;
    void SetGroupTip(QString str);
private:
    Ui::GroupTipItem *ui;
    QString _tip;
};


#endif //CLIENT_GROUPTIPITEM_H
