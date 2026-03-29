//
// Created by 86157 on 2026/3/28.
//

#ifndef CLIENT_CLICKEDBTN_H
#define CLIENT_CLICKEDBTN_H


#include <QPushButton>
#include <QMenu>
#include <QAction>

// 定义信号枚举，方便外部区分用户点击了哪个选项
enum class MenuAction {
    CreateGroup,
    AddFriend,
};

class ClickedBtn : public QPushButton
{
Q_OBJECT

public:
    explicit ClickedBtn(QWidget *parent = nullptr);

signals:
    // 当菜单项被点击时发出的信号，携带动作类型
    void actionTriggered(MenuAction action);

private slots:
    void onActionTriggered(QAction *action);

private:
    QMenu *m_menu; // 菜单指针
};

#endif //CLIENT_CLICKEDBTN_H
