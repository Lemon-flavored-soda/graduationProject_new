//
// Created by 86157 on 2026/3/20.
//

// You may need to build the project (run Qt uic code generator) to get "ui_register_dialog.h" resolved

#include "../Headers/register_dialog.h"
#include "ui_register_dialog.h"
#include "../Headers/httpmgr.h"
#include "../Headers/Toast.h"
#include <QJsonObject>

RegisterDialog::RegisterDialog(QWidget *parent) :
        QWidget(parent), ui(new Ui::RegisterDialog) {
    ui->setupUi(this);
    initHttpHandlers();
    QPixmap pix(":/image/QQ_1.png");
    this->setWindowIcon(pix);
    ui->send_message->setCursor(Qt::PointingHandCursor);
    ui->send_message->installEventFilter(this);
    ui->send_message->setEnabled(false);
    memset(flag,0,sizeof(flag));
    ui->code->setEchoMode(QLineEdit::Password);
    connect(ui->pass_visible, &ClickedLabel::clicked,this,[=](){
        ui->code->setEchoMode(QLineEdit::Normal);
    });
    connect(ui->pass_visible, &ClickedLabel::release,this,[=](){
        ui->code->setEchoMode(QLineEdit::Password);
    });
    //get()得到裸指针来获取信号
    connect(HttpMgr::GetInstance().get(), &HttpMgr::sig_reg_mod_finish,
            this, &RegisterDialog::slot_reg_mod_finish);



    connect(ui->nickname,&QLineEdit::editingFinished,this,[this](){
        //检测用户是否合理
        flag[0] = checkUserValid();
    });

    connect(ui->code, &QLineEdit::editingFinished, this, [this](){
        //检测密码是否合理
        flag[1] = checkPassValid();
    });

    connect(ui->phone, &QLineEdit::editingFinished, this, [this](){
        //检测邮件是否合理
        flag[2] = checkEmailValid();
        if(flag[2]){
            ui->send_message->setEnabled(true);
        }
        else{
            ui->send_message->setEnabled(false);
        }
    });

    connect(ui->message, &QLineEdit::editingFinished, this, [this](){
        //检测验证码是否合理
        flag[3] = checkVarifyValid();
    });

    ui->pass_visible->setCursor(Qt::PointingHandCursor);


}

RegisterDialog::~RegisterDialog() {
    delete ui;
}


void RegisterDialog::slot_reg_mod_finish(ReqId id, QString res, ErrorCodes err) {


    if(err != ErrorCodes::SUCCESS){
        Toast::showMessage(this, "请求超时", 3000);
        return;
    }

    //解析JSON字符串，res转化为QByteArray
    QJsonDocument jsonDoc = QJsonDocument::fromJson(res.toUtf8());
    if(jsonDoc.isNull()){
        Toast::showMessage(this, "json解析失败", 3000);
        return;
    }
    //json解析错误
    if(!jsonDoc.isObject()){
        Toast::showMessage(this, "json解析失败", 3000);
        return;
    }

    handlers[id](jsonDoc.object());
    return;

}

bool RegisterDialog::checkUserValid()
{
    if(ui->nickname->text() == ""){
        Toast::showMessage(this, "昵称不能为空", 3000);
        return false;
    }

    return true;
}

bool RegisterDialog::checkEmailValid()
{
    //验证邮箱的地址正则表达式
    auto email = ui->phone->text();
    // 邮箱地址的正则表达式
    QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    bool match = regex.match(email).hasMatch(); // 执行正则表达式匹配
    if(!match){
        //提示邮箱不正确
        Toast::showMessage(this, "邮箱地址不正确", 3000);
        return false;
    }
    return true;
}

bool RegisterDialog::checkPassValid()
{
    auto pass = ui->code->text();

    if(pass.length() < 6 || pass.length()>15){
        //提示长度不准确
        Toast::showMessage(this, "密码长度应为6~15", 3000);
        return false;
    }

    // 创建一个正则表达式对象，按照上述密码要求
    // 这个正则表达式解释：
    // ^[a-zA-Z0-9!@#$%^&*]{6,15}$ 密码长度至少6，可以是字母、数字和特定的特殊字符
    QRegularExpression regExp("^[a-zA-Z0-9!@#$%^&*.]{6,15}$");
    bool match = regExp.match(pass).hasMatch();
    if(!match){
        //提示字符非法
        Toast::showMessage(this, "不能包含非法字符", 3000);
        return false;;
    }
    return true;
}

bool RegisterDialog::checkVarifyValid()
{
    auto pass = ui->message->text();
    if(pass.isEmpty()){
        Toast::showMessage(this, "验证码不能为空", 3000);
        return false;
    }
    return true;
}


void RegisterDialog::initHttpHandlers() {
    //注册获取验证码回包的逻辑
    handlers.insert(ReqId::ID_GET_VARIFY_CODE, [this](const QJsonObject& jsonObj){
        int error = jsonObj["error"].toInt();
        if(error != ErrorCodes::SUCCESS){
            Toast::showMessage(this, "参数错误", 3000);
            return;
        }
        auto email = jsonObj["email"].toString();
        Toast::showMessage(this, "验证码已经发送邮箱，注意查收", 3000);
        qDebug() << "email is " << email;
    });

    handlers.insert(ReqId::ID_REG_USER, [this](QJsonObject jsonObj) {
        int error = jsonObj["error"].toInt();
        if (error != ErrorCodes::SUCCESS) {
            Toast::showMessage(this, "参数错误", 3000);
            return;
        }
        auto email = jsonObj["email"].toString();
        Toast::showMessage(this, "用户注册成功", 3000);
        qDebug() << "user uuid is" << jsonObj["uuid"].toString();
        qDebug() << "email is " << email;
    });
}

bool RegisterDialog::eventFilter(QObject *watched, QEvent *event) {
    if (watched == ui->send_message) {
        if (event->type() == QEvent::MouseButtonPress) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if(mouseEvent->button() == Qt::LeftButton){
                //qDebug() << "Label 被点击了！";
                auto email = ui->phone->text();
                QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
                bool match = regex.match(email).hasMatch();
                if(match){
                    //发送http验证码
                    QJsonObject json_obj;
                    json_obj["email"] = email;
                    HttpMgr::GetInstance()->PostHttpReq(QUrl(gate_url_prefix + "/get_varifycode"),
                                                        json_obj,ReqId::ID_GET_VARIFY_CODE,Modules::REGISTERMOD);
                }else{
                    Toast::showMessage(this, "邮箱地址不正确", 3000);
                }
                return true; // 返回 true 表示事件已处理，不再传递给 QLabel 默认行为
            }

        }
    }
    return QObject::eventFilter(watched, event);
}

//添加注册槽函数
void RegisterDialog::on_register_now_clicked()
{
    if(!flag[0]){
        checkUserValid();
        return;
    }

    if(!flag[1]){
        checkPassValid();
        return;
    }

    if(!flag[2]){
        checkEmailValid();
        return;
    }


    if(!flag[3]){
        checkVarifyValid();
        return;
    }

    // 发送http请求注册用户
    QJsonObject json_obj;
    json_obj["user"] = ui->nickname->text();
    json_obj["email"] = ui->phone->text();
    json_obj["passwd"] = xorString(ui->code->text());
    json_obj["varifycode"] = ui->message->text();
    HttpMgr::GetInstance()->PostHttpReq(QUrl(gate_url_prefix+"/user_register"),
                                        json_obj, ReqId::ID_REG_USER,Modules::REGISTERMOD);
}


