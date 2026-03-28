//
// Created by 86157 on 2026/3/20.
//

#ifndef CLIENT_HTTPMGR_H
#define CLIENT_HTTPMGR_H
#include "singleton.h"
#include <QString>
//Qt Http路由发送
#include <QUrl>
#include <QObject>
//网络管理
#include <QNetworkAccessManager>
//将对象通过json序列化成字符串扔给对方
#include <QJsonArray>
//方便反序列化，解析json
#include <QJsonDocument>
#include <QJsonObject>

//单例http管理者,CRTP 奇异递归模板模式(类能继承以自己为类型的模板类)
class HttpMgr : public QObject, public Singleton<HttpMgr>,
        public std::enable_shared_from_this<HttpMgr>{
    Q_OBJECT
public:
    ~HttpMgr();
    //定义发送的函数(网址路由，json数据，功能id，模块)
    void PostHttpReq(QUrl url, QJsonObject json, ReqId req_id, Modules mod);
private:
    //使得基类能够访问子类的构造函数
    friend class Singleton<HttpMgr>;
    HttpMgr();
    QNetworkAccessManager manager;

private slots:
    void slot_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod);
signals:
    void sig_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod);
    void sig_reg_mod_finish(ReqId id, QString res, ErrorCodes err);
    void sig_login_mod_finish(ReqId id, QString res, ErrorCodes err);
};


#endif //CLIENT_HTTPMGR_H
