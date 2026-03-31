//
// Created by 86157 on 2026/3/30.
//

#ifndef CLIENT_LISTITEMBASE_H
#define CLIENT_LISTITEMBASE_H
#include <QWidget>
#include "global.h"

class ListItemBase : public QWidget{
    Q_OBJECT
public:
    explicit ListItemBase(QWidget* parent = nullptr);
    void SetItemType(ListItemType itemType);
    ListItemType GetItemType();
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    ListItemType _itemType;
public slots:

signals:

};


#endif //CLIENT_LISTITEMBASE_H
