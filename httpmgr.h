#ifndef HTTPMGR_H
#define HTTPMGR_H
#include "singleton.h"
#include<QString>
#include<QUrl>
#include<QObject>
#include<QNetworkAccessManager>//需要qt的网络
#include<QJsonObject>//发送数据 底层字节流的传输 需要json序列化车该字符串
#include<QJsonDocument>// 方便反序列化
//CRTP
class HttpMgr:public QObject,public Singleton<HttpMgr>,
                public std::enable_shared_from_this<HttpMgr>
{
    Q_OBJECT
public:
    ~ HttpMgr();
private:
    //积累访问子类的构造函数
    friend class Singleton<HttpMgr>;
    HttpMgr();
    QNetworkAccessManager _manager;
    //发送信号； 参数：路由 异步：hppt发送之后会回调 什么时候回调不知道 req_id方便知道那个模块

    void PostHttpReq(QUrl url, QJsonObject json, ReqId req_id, Modules mod);
private slots:
    void slot_http_finish(ReqId req_id, const QString& response, ErrorCodes error, Modules mod);
signals:

    void sig_http_finish(ReqId req_id, const QString& response, ErrorCodes error, Modules mod);
    void sig_reg_mod_finish(ReqId id,  QString& res, ErrorCodes err);
};

#endif // HTTPMGR_H
