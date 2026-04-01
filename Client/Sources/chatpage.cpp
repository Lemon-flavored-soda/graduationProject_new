//
// Created by 86157 on 2026/3/30.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ChatPage.h" resolved

#include "chatpage.h"
#include "ui_ChatPage.h"
#include <QStyleOption>
#include <QPainter>
#include <QJsonDocument>
#include "ChatItemBase.h"
#include "TextBubble.h"
#include "PictureBubble.h"
#include "usermgr.h"
#include <QJsonArray>
#include <QJsonObject>
#include "tcpmgr.h"
#include <QUuid>


ChatPage::ChatPage(QWidget *parent) :
        QWidget(parent), ui(new Ui::ChatPage) {
    ui->setupUi(this);


    //设置按钮样式
    ui->send_btn->SetState("normal","hover","press");

    //设置图标样式
    ui->emo->SetState("normal","hover","press","normal","hover","press");
    ui->file->SetState("normal","hover","press","normal","hover","press");

}

ChatPage::~ChatPage() {
    delete ui;
}

void ChatPage::SetUserInfo(std::shared_ptr<UserInfo> user_info)
{
    _user_info = user_info;
    //设置ui界面
    ui->title_lb->setText(_user_info->_name);
    ui->chat_view->removeAllItem();
    for(auto & msg : user_info->_chat_msgs){
        AppendChatMsg(msg);
    }
}

void ChatPage::AppendChatMsg(std::shared_ptr<TextChatData> msg)
{
    auto self_info = UserMgr::GetInstance()->GetUserInfo();
    ChatRole role;
    //todo... 添加聊天显示
    if (msg->_from_uid == self_info->_uid) {
        role = ChatRole::Self;
        ChatItemBase* pChatItem = new ChatItemBase(role);

        pChatItem->setUserName(self_info->_name);
        pChatItem->setUserIcon(QPixmap(self_info->_icon));
        QWidget* pBubble = nullptr;
        pBubble = new TextBubble(role, msg->_msg_content);
        pChatItem->setWidget(pBubble);
        ui->chat_view->appendChatItem(pChatItem);
    }
    else {
        role = ChatRole::Other;
        ChatItemBase* pChatItem = new ChatItemBase(role);
        auto friend_info = UserMgr::GetInstance()->GetFriendById(msg->_from_uid);
        if (friend_info == nullptr) {
            return;
        }
        pChatItem->setUserName(friend_info->_name);
        pChatItem->setUserIcon(QPixmap(friend_info->_icon));
        QWidget* pBubble = nullptr;
        pBubble = new TextBubble(role, msg->_msg_content);
        pChatItem->setWidget(pBubble);
        ui->chat_view->appendChatItem(pChatItem);
    }


}

void ChatPage::paintEvent(QPaintEvent *event) {
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget,&opt,&p,this);
}

void ChatPage::on_send_btn_clicked() {
    auto pTextEdit = ui->chatEdit;
    ChatRole role = ChatRole::Self;
    QString userName = QStringLiteral("柠檬味汽水");
    QString userIcon = ":/image/工程师.png";
    const QVector<MsgInfo>& msgList = pTextEdit->getMsgList();
    for(int i=0; i<msgList.size(); i++){
        QString type = msgList[i].msgFlag;
        ChatItemBase* pChatItem = new ChatItemBase(role);
        pChatItem->setUserName(userName);
        pChatItem->setUserIcon(QPixmap(userIcon));
        QWidget* pBubble = nullptr;
        if(type == "text"){
            pBubble = new TextBubble(role, msgList[i].content);
        }
        else if(type == "image"){
            pBubble = new PictureBubble(QPixmap(msgList[i].content),role);
        }
        else if(type == "file"){

        }
        if(pBubble != nullptr){
            pChatItem->setWidget(pBubble);
            ui->chat_view->appendChatItem(pChatItem);
        }
    }
}

void ChatPage::on_receive_btn_clicked() {

}
