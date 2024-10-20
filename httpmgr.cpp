#include "httpmgr.h"

HttpMgr::~HttpMgr()
{

}

HttpMgr::HttpMgr()
{
    connect(this,&HttpMgr::sig_http_finish,this,&HttpMgr::slot_http_finish);
}
void HttpMgr::PostHttpReq(QUrl url, QJsonObject json, ReqId req_id, Modules mod)
{
    //创建http请求 首先发送数据 把json对象序列化一个字符串json
    QByteArray data=QJsonDocument(json).toJson();
    QNetworkRequest request(url);
    //设置一些头部http基于tcp  用完断开  发送类型长度
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    request.setHeader(QNetworkRequest::ContentTypeHeader, QByteArray::number(data.length()));
    //保证回调HTTP manager、 外部智能指针 内部商城稚嫩那个指针 内部生成selselff智能指针
    auto self=shared_from_this();
    QNetworkReply * reply=_manager.post(request,data);
    QObject::connect(reply,&QNetworkReply::finished,[self,reply,req_id,mod](){
        //直接写表达式肯定用到HttpMgr里面的数据 保证回调HTTP manager、 外部智能指针 内部商城稚嫩那个指针
        //self 被捕获了放到表达式里作为成员变量
        //处理错误
        if(reply->error()!=QNetworkReply::NoError){
            QDebug()<<reply->errorString();        //发送信号完成
            emit self->sig_http_finish(req_id, "", ErrorCodes::ERR_NETWORK, mod);
            reply->deleteLater();
            return;
        }
        //无错误
        QString res =reply->readAll();
        //发送完成的信号
       emit self->sig_http_finish(req_id, res, ErrorCodes::SUCCESS, mod);
        reply->deleteLater();
       return;
    });
}
void HttpMgr::slot_http_finish(ReqId req_id, const QString& response, ErrorCodes error, Modules mod)
{
    if(mod==Modules::REGISTERMOD)
    {
        //发送信号通知模块http的相应结束了
        emit sig_reg_mod_finish(id,res,err);
    }
}
