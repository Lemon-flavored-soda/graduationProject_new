//
// Created by 86157 on 2026/3/27.
//

// You may need to build the project (run Qt uic code generator) to get "ui_chat_dialog.h" resolved

#include "chat_dialog.h"
#include "ui_chat_dialog.h"
#include <QAction>


ChatDialog::ChatDialog(QWidget *parent) :
        QDialog(parent), ui(new Ui::ChatDialog) {
    ui->setupUi(this);
    QPixmap pixmap(":/image/消息_2.png");
    ui->message->setPixmap(pixmap.scaled(30,30,Qt::KeepAspectRatio,Qt::SmoothTransformation));
    pixmap = QPixmap(":/image/联系人.png");
    ui->boy->setPixmap(pixmap.scaled(30,30,Qt::KeepAspectRatio,Qt::SmoothTransformation));
    pixmap = QPixmap(":/image/表情.png");
    ui->emo->setPixmap(pixmap.scaled(20,20,Qt::KeepAspectRatio,Qt::SmoothTransformation));
    pixmap = QPixmap(":/image/文件夹.png");
    ui->file->setPixmap(pixmap.scaled(20,20,Qt::KeepAspectRatio,Qt::SmoothTransformation));

    ui->search_edit->SetMaxLength(15);
    //通过Action触发菜单
    QAction* searchAction = new QAction(ui->search_edit);
    searchAction->setIcon(QIcon(":/image/搜索.png"));
    ui->search_edit->addAction(searchAction,QLineEdit::LeadingPosition);
    //设置默认文本
    ui->search_edit->setPlaceholderText(QStringLiteral("搜索"));
    //创建一个清除动作并设置图标
    QAction* clearAction = new QAction(ui->search_edit);
    clearAction->setIcon(QIcon(":/image/空白.png"));
    //初始时不显示清楚图标
    //将清除动作添加到LineEdit的末尾位置
    ui->search_edit->addAction(clearAction,QLineEdit::TrailingPosition);
    //当需要显示清除图标时，更改为实际的清除图标
    connect(ui->search_edit,&QLineEdit::textChanged,[clearAction](const QString& text){
        if(!text.isEmpty()){
            clearAction->setIcon(QIcon(":/image/关闭.png"));
        }
        else{
            clearAction->setIcon(QIcon(":/image/空白.png"));
        }
    });
    //连接清除动作的触发信号到槽函数，用于清除文本
    connect(clearAction,&QAction::triggered,[this,clearAction](){
       ui->search_edit->clear();
       clearAction->setIcon(QIcon(":/image/空白.png"));//清除文本后，切换回透明图标
       ui->search_edit->clearFocus();

    });


    //ui->chat_user_wig->setStyleSheet("background-color:rgb(0,0,0);");
    //ui->chat_user_list->setStyleSheet("background-color:rgb(247,247,248);border:none;");

}

ChatDialog::~ChatDialog() {
    delete ui;
}

void ChatDialog::ShowSearch(bool bsearch) {
    if(bsearch){
        ui->chat_user_list->hide();
        ui->con_user_list->hide();
        ui->search_list->show();

    }

}
