//
// Created by 86157 on 2026/4/2.
//

#ifndef CLIENT_APPLYFRIENDLIST_H
#define CLIENT_APPLYFRIENDLIST_H
#include <QListWidget>
#include <QEvent>

class ApplyFriendList : public QListWidget{
    Q_OBJECT
public:
    ApplyFriendList(QWidget* parent = nullptr);
protected:
    bool eventFilter(QObject *object, QEvent *event) override;
private slots:

signals:
    void sig_show_search(bool);
};


#endif //CLIENT_APPLYFRIENDLIST_H
