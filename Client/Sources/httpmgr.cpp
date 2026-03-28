//
// Created by 86157 on 2026/3/20.
//

#include "../Headers/httpmgr.h"

HttpMgr::HttpMgr() {
    connect(this, &HttpMgr::sig_http_finish, this, &HttpMgr::slot_http_finish);

}

HttpMgr::~HttpMgr() {

}

void HttpMgr::PostHttpReq(QUrl url, QJsonObject json, ReqId req_id, Modules mod) {
    //json对象被序列化为字节数组
    QByteArray data = QJsonDocument(json).toJson();
    //创建Http请求
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::ContentTypeHeader,QByteArray::number(data.length()));
    auto self = shared_from_this();
    //发送请求
    QNetworkReply* reply = manager.post(request, data);
    QObject::connect(reply, &QNetworkReply::finished, [self, reply, req_id, mod](){
        //处理错误情况
        if(reply->error() != QNetworkReply::NoError){
            qDebug() <<  reply->errorString();
            //发送信号通知完成
            emit self->sig_http_finish(req_id, "", ErrorCodes::ERR_NETWORK, mod);
            reply->deleteLater();
            return;
        }
        //无错误
        QString res = reply->readAll();
        //发送信号通知完成
        emit self->sig_http_finish(req_id, res, ErrorCodes::SUCCESS, mod);
        reply->deleteLater();
        return;
    });

}

void HttpMgr::slot_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod) {
    if(mod == Modules::REGISTERMOD){
        //发送信号通知指定模块http的响应结束了
        emit sig_reg_mod_finish(id, res, err);
    }
}

