#ifndef GLOBAL_H
#define GLOBAL_H
#include<QWidget>
#include<memory>//用到智能指针
#include<iostream>
#include<mutex>
#include<QByteArray>
#include<functional>
#include<QRegularExpression>//正则表达式
#include<QNetworkReply>

//repolish用来刷新qss

#include"QStyle"
extern std::function<void(QWidget*)>repolish;
enum ReqId{
    ID_GET_VERIFY_CODE=1001,//获取验证码
    ID_REG_USER=1002,//注册用户
};
enum Modules{
    REGISTERMOD =0 ,
};
enum ErrorCodes{
    SUCCESS =0,
    ERR_JSON=1,//JSON解析失败
    ERR_NETWORK=2,//网络错误
};

#endif // GLOBAL_H
