//
// Created by 86157 on 2026/3/27.
//

// You may need to build the project (run Qt uic code generator) to get "ui_chat_dialog.h" resolved

#include "chat_dialog.h"
#include "ui_chat_dialog.h"
#include <QAction>
#include <QRandomGenerator>
#include "chatuserwid.h"
#include "loadingdlg.h"
#include <QMouseEvent>
#include "global.h"


ChatDialog::ChatDialog(QWidget *parent) :
        QDialog(parent), ui(new Ui::ChatDialog),_mode(ChatUIMode::ChatMode),
        _state(ChatUIMode::ChatMode),b_loading(false) {
    ui->setupUi(this);


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
        //清除按钮被按下则不显示搜索框
        ShowSearch(false);
    });

    ShowSearch(false);
    connect(ui->chat_user_list,&ChatUserList::sig_loading_chat_user,this, &ChatDialog::slot_loading_chat_user);
    addChatUserList();

    ui->side_chat_lb->setProperty("state","normal");
    ui->side_chat_lb->SetState("normal","hover","pressed","selected_normal","selected_hover","selected_pressed");
    ui->side_contact_lb->SetState("normal","hover","pressed","selected_normal","selected_hover","selected_pressed");

    AddLBGroup(ui->side_chat_lb);
    AddLBGroup(ui->side_contact_lb);

    connect(ui->side_chat_lb,&StateWidget::clicked,this,&ChatDialog::slot_side_chat);
    connect(ui->side_contact_lb,&StateWidget::clicked,this,&ChatDialog::slot_side_contact);
    //链接搜索框输入变化
    connect(ui->search_edit,&QLineEdit::textChanged,this,&ChatDialog::slot_text_changed);
    //检测鼠标点击位置判断是否清空搜索框
    this->installEventFilter(this);//安装事件过滤器
    //设置聊天label选中状态
    ui->side_chat_lb->SetSelected(true);
}

ChatDialog::~ChatDialog() {
    delete ui;
}

void ChatDialog::ShowSearch(bool bsearch) {
    if(bsearch){
        ui->chat_user_list->hide();
        ui->con_user_list->hide();
        ui->search_list->show();
        _mode = ChatUIMode::SearchMode;
    }else if(_state == ChatUIMode::ChatMode){
        ui->chat_user_list->show();
        ui->con_user_list->hide();
        ui->search_list->hide();
        _mode = ChatUIMode::ChatMode;
        ui->search_list->CloseFindDlg();
        ui->search_edit->clear();
        ui->search_edit->clearFocus();
    }else if(_state == ChatUIMode::ContactMode){
        ui->chat_user_list->hide();
        ui->search_list->hide();
        ui->con_user_list->show();
        _mode = ChatUIMode::ContactMode;
        ui->search_list->CloseFindDlg();
        ui->search_edit->clear();
        ui->search_edit->clearFocus();
    }
//    else if(_state == ChatUIMode::SettingsMode){
//        ui->chat_user_list->hide();
//        ui->search_list->hide();
//        ui->con_user_list->show();
//        _mode = ChatUIMode::ContactMode;
//        ui->search_list->CloseFindDlg();
//        ui->search_edit->clear();
//        ui->search_edit->clearFocus();
//    }

}

//测试
void ChatDialog::addChatUserList() {
    //创建QListWidgetItem，并设置自定义的widget
    for(int i = 0; i < 13; i++){
        //生成0到99之间的随机整数
        int randomValue = QRandomGenerator::global()->bounded(100);
        int str_i = randomValue%strs.size();
        int head_i = randomValue%heads.size();
        int name_i = randomValue%names.size();

        auto* chat_user_wid = new ChatUserWid();
        chat_user_wid->SetInfo(names[name_i],heads[head_i],strs[str_i]);
        QListWidgetItem* item = new QListWidgetItem();
        item->setSizeHint(chat_user_wid->sizeHint());
        ui->chat_user_list->addItem(item);
        ui->chat_user_list->setItemWidget(item, chat_user_wid);
    }
}

void ChatDialog::slot_loading_chat_user() {
    if(b_loading){
        return;
    }
    b_loading = true;
    LoadingDlg* loadingDialog = new LoadingDlg(this);
    loadingDialog->setModal(true);
    loadingDialog->show();
    qDebug() << "add new data to list ...";
    addChatUserList();
    //加载后关闭对话框
    loadingDialog->deleteLater();
    b_loading = false;
}

void ChatDialog::AddLBGroup(StateWidget(* lb)) {
    _lb_list.push_back(lb);
}

void ChatDialog::slot_side_chat() {
    ClearLabelState(ui->side_chat_lb);
    ui->stackedWidget->setCurrentWidget(ui->chat_page);
    _state = ChatUIMode::ChatMode;
    ShowSearch(false);
}

void ChatDialog::slot_side_contact() {
    ClearLabelState(ui->side_contact_lb);
    //设置
    ui->stackedWidget->setCurrentWidget(ui->friend_apply_page);
    _state = ChatUIMode::ContactMode;
    ShowSearch(false);
}

void ChatDialog::ClearLabelState(StateWidget *lb) {
    for(auto& ele:_lb_list){
        if(ele == lb)continue;
        ele->ClearState();
    }
}

void ChatDialog::slot_text_changed(const QString &str) {
    if(!str.isEmpty()){
        ShowSearch(true);
    }
}

bool ChatDialog::eventFilter(QObject *watched, QEvent *event) {
    if(event->type() == QEvent::MouseButtonPress){
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        handleGlobalMousePress(mouseEvent);
    }
    return QDialog::eventFilter(watched,event);
}

void ChatDialog::handleGlobalMousePress(QMouseEvent *event) {
    //实现点击位置的判断和处理逻辑
    //先判断是否处于搜索模式，如果不处于搜索模式则直接返回
    if(_mode != ChatUIMode::SearchMode)return;
    //将鼠标点击位置转换为搜索列表坐标系中的位置
    QPoint posInSearchList = ui->search_list->mapFromGlobal(event->globalPos());
    //判断点击位置是否在聊天列表的范围内
    if(!ui->search_list->rect().contains(posInSearchList)){
        //如果不在聊天列表内，清空输入框
        ui->search_edit->clear();
        ShowSearch(false);
    }
}

