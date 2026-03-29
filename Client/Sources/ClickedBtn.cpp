//
// Created by 86157 on 2026/3/28.
//

#include "ClickedBtn.h"
#include "global.h"
#include <QVariant>


ClickedBtn::ClickedBtn(QWidget *parent)
        : QPushButton(parent), m_menu(new QMenu(this))
{
    // 1. 设置按钮样式（模拟你截图中的灰色圆角按钮）
    this->setStyleSheet(
            "QPushButton {"
            "   background-color: #E0E0E0;"
            "   border-radius: 4px;"
            "   padding: 5px;"
            "}"
            "QPushButton:hover {"
            "   background-color: gray;"
            "}"
            "QMenu {"
            "   background-color: white;"           // 背景颜色
            "   border: 1px solid #D3D3D3;"         // 边框
            "   border-radius: 6px;"                // 圆角
            "   padding: 5px;"                      // 内边距
            "   margin: 0px;"                       // 外边距
            "}"
            "QMenu::item {"
            "   padding: 8px 25px 8px 30px;"        // 左边留出空间给图标，右边留出空间给快捷键
            "   border: 1px solid transparent;"     // 为了美观，先设为透明
            "}"
            "QMenu::item:selected {"
            "   background-color: #F0F0F0;"         // 鼠标悬停时的背景色
            "   color: black;"                      // 文字颜色
            "}"
            "QMenu::icon {"
            "   left: 10px;"                        // 图标距离左边的距离
            "}"
            "QMenu::separator {"
            "   height: 1px;"
            "   background-color: #D3D3D3;"
            "   margin: 5px 0px;"
            "}"
    );

    // 2. 设置按钮文本或图标
    this->setIcon(QIcon(":/image/004_加好友.png"));

    // 3. 构建菜单项
    QAction *actCreateGroup = m_menu->addAction("创建群聊");
    QAction *actAddFriend = m_menu->addAction("加好友/群");

    // 4. 关联菜单项触发信号
    connect(m_menu, &QMenu::triggered, this, &ClickedBtn::onActionTriggered);

    // 5. 关键：连接按钮的点击信号到菜单的弹出槽
    // 当按钮被点击时，显示菜单
    connect(this, &QPushButton::clicked, this, [this]() {
        // 使用 exec() 在按钮下方弹出菜单
        m_menu->exec(this->mapToGlobal(QPoint(0, this->height())));
    });
}

void ClickedBtn::onActionTriggered(QAction *action)
{
    // 根据触发的 QAction 文本判断用户选择了什么
    if (action->text() == "创建群聊") {
        emit actionTriggered(MenuAction::CreateGroup);
    } else if (action->text() == "加好友/群") {
        emit actionTriggered(MenuAction::AddFriend);
    }
}
