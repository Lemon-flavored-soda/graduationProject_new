//
// Created by 86157 on 2026/4/2.
//

#ifndef CLIENT_APPLYFRIENDPAGE_H
#define CLIENT_APPLYFRIENDPAGE_H

#include <QWidget>
#include "userdata.h"
#include <memory>
#include <QJsonArray>
#include <unordered_map>
#include "ListItemBase.h"
#include "applyfrienditem.h"


QT_BEGIN_NAMESPACE
namespace Ui { class ApplyFriendPage; }
QT_END_NAMESPACE

class ApplyFriendPage : public QWidget {
Q_OBJECT

public:
    explicit ApplyFriendPage(QWidget *parent = nullptr);
    ~ApplyFriendPage();
    void AddNewApply(std::shared_ptr<AddFriendApply> apply);
protected:
    void paintEvent(QPaintEvent *event);
private:
    void loadApplyList();
    Ui::ApplyFriendPage *ui;
    std::unordered_map<int, ApplyFriendItem*> _unauth_items;
public slots:
    void slot_auth_rsp(std::shared_ptr<AuthRsp> );
signals:
    void sig_show_search(bool);
};


#endif //CLIENT_APPLYFRIENDPAGE_H
