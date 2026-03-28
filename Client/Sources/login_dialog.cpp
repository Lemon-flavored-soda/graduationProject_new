//
// Created by 86157 on 2026/3/19.
//

// You may need to build the project (run Qt uic code generator) to get "ui_login_dialog.h" resolved

#include "../Headers/login_dialog.h"
#include "ui_login_dialog.h"
#include <QPainter>
#include <QPainterPath>
#include "../Headers/Toast.h"
#include "../Headers/httpmgr.h"
#include "../Headers/TcpMgr.h"


LoginDialog::LoginDialog(QWidget *parent) :
        QDialog(parent), ui(new Ui::LoginDialog) {
    ui->setupUi(this);
    QPixmap pix(":/image/QQ_1.png");
    ui->head_label->setPixmap(pix);
    this->setWindowIcon(pix);
    ui->head_label->setScaledContents(true);
    ui->register_num->setStyleSheet("color: #2D77E5; font-weight: bold;");
    ui->code_login->setStyleSheet("color: #2D77E5; font-weight: bold;");
    //ui->btn_login->setEnabled(false);

    ui->register_num->setCursor(Qt::PointingHandCursor); // 变成手型，提示可点击
    // 核心：安装事件过滤器
    ui->register_num->installEventFilter(this);

    initHttpHandlers();
    //连接登录回包信号
    connect(HttpMgr::GetInstance().get(), &HttpMgr::sig_login_mod_finish,this,
            &LoginDialog::slot_login_mod_finish);

    //连接tcp连接请求的信号和槽函数
    connect(this, &LoginDialog::sig_connect_tcp, TcpMgr::GetInstance().get(), &TcpMgr::slot_tcp_connect);
    //连接tcp管理者发出的连接成功信号
    connect(TcpMgr::GetInstance().get(), &TcpMgr::sig_con_success, this, &LoginDialog::slot_tcp_con_finish);
    //连接tcp管理者发出的登陆失败信号
    connect(TcpMgr::GetInstance().get(), &TcpMgr::sig_login_failed, this, &LoginDialog::slot_login_failed);
}

LoginDialog::~LoginDialog() {
    delete ui;
}


bool LoginDialog::eventFilter(QObject *watched, QEvent *event) {
    if (watched == ui->register_num) {
        if (event->type() == QEvent::MouseButtonPress) {
            //qDebug() << "Label 被点击了！";
            rg_dialog = new RegisterDialog();
            //设置属性：关闭窗口时自动 delete 对象
            rg_dialog->setAttribute(Qt::WA_DeleteOnClose);
            //rg_dialog->setWindowModality(Qt::ApplicationModal);
            rg_dialog->show();
            return true; // 返回 true 表示事件已处理，不再传递给 QLabel 默认行为
        }
    }
    // 其他事件交给基类处理
    return QWidget::eventFilter(watched, event);
}

void LoginDialog::on_btn_login_clicked() {
    if(checkUserValid() == false){
        return;
    }

    if(checkPwdValid() == false){
        return ;
    }

    //ui->btn_login->setEnabled(false);
    auto email = ui->user_edit->text();
    auto pwd = ui->pass_edit->text();
    //发送http请求登录
    QJsonObject json_obj;
    json_obj["email"] = email;
    json_obj["passwd"] = xorString(pwd);
    HttpMgr::GetInstance()->PostHttpReq(QUrl(gate_url_prefix+"/user_login"),
                                        json_obj, ReqId::ID_LOGIN_USER,Modules::LOGINMOD);
}

bool LoginDialog::checkUserValid() {
    auto email = ui->user_edit->text();
    if(email.isEmpty()){
        Toast::showMessage(this, "QQ号不能为空", 3000);
        return false;
    }
    return true;
}

bool LoginDialog::checkPwdValid() {
    auto pwd = ui->pass_edit->text();
    if(pwd.length() < 6 || pwd.length() > 15){
        //提示长度不准确
        Toast::showMessage(this, "密码长度应为6~15", 3000);
        return false;
    }

    // 创建一个正则表达式对象，按照上述密码要求
    // 这个正则表达式解释：
    // ^[a-zA-Z0-9!@#$%^&*]{6,15}$ 密码长度至少6，可以是字母、数字和特定的特殊字符
    QRegularExpression regExp("^[a-zA-Z0-9!@#$%^&*.]{6,15}$");
    bool match = regExp.match(pwd).hasMatch();
    if(!match){
        //提示字符非法
        Toast::showMessage(this, "不能包含非法字符且长度为(6~15)", 3000);
        return false;;
    }
    return true;
}

void LoginDialog::initHttpHandlers() {
    //注册获取登录回包逻辑
    _handlers.insert(ReqId::ID_LOGIN_USER, [this](QJsonObject jsonObj){
        int error = jsonObj["error"].toInt();
        if(error != ErrorCodes::SUCCESS){
            Toast::showMessage(this, "参数错误", 3000);
            return;
        }
        auto email = jsonObj["email"].toString();

        //发送信号通知tcpMgr发送长链接
        ServerInfo si; //服务器的回包信息
        si.Uid = jsonObj["uid"].toInt();
        si.Host = jsonObj["host"].toString();
        si.Port = jsonObj["port"].toString();
        si.Token = jsonObj["token"].toString();

        _uid = si.Uid;
        _token = si.Token;
        qDebug()<< "email is " << email << " uid is " << si.Uid <<" host is "
                << si.Host << " Port is " << si.Port << " Token is " << si.Token;
        emit sig_connect_tcp(si);
    });
}


void LoginDialog::slot_login_mod_finish(ReqId id, QString res, ErrorCodes err) {
    if(err != ErrorCodes::SUCCESS){
        Toast::showMessage(this, "网络请求错误", 3000);
        return;
    }

    // 解析 JSON 字符串,res需转化为QByteArray
    QJsonDocument jsonDoc = QJsonDocument::fromJson(res.toUtf8());
    //json解析错误
    if(jsonDoc.isNull()){
        Toast::showMessage(this, "json解析错误", 3000);
        return;
    }

    //json解析错误
    if(!jsonDoc.isObject()){
        Toast::showMessage(this, "json解析错误", 3000);
        return;
    }


    //调用对应的逻辑,根据id回调。
    _handlers[id](jsonDoc.object());

    return;
}

void LoginDialog::slot_tcp_con_finish(bool bsuccess)
{

    if(bsuccess){
        Toast::showMessage(this, "聊天服务连接成功，正在登录...", 3000);
        QJsonObject jsonObj;
        jsonObj["uid"] = _uid;
        jsonObj["token"] = _token;

        QJsonDocument doc(jsonObj);
        QByteArray jsonData = doc.toJson(QJsonDocument::Indented);

        //发送tcp请求给chat server
        emit TcpMgr::GetInstance()->sig_send_data(ReqId::ID_CHAT_LOGIN, jsonData);

    }else{
        Toast::showMessage(this, "网络异常", 3000);
        ui->btn_login->setEnabled(true);
    }

}

void LoginDialog::slot_login_failed(int err)
{
    QString result = QString("登录失败, err is %1")
            .arg(err);
    Toast::showMessage(this, result, 3000);
    ui->btn_login->setEnabled(true);
}