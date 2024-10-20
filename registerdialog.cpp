#include "registerdialog.h"
#include "ui_registerdialog.h"
#include"global.h"
#include"httpmgr.h"//在http里面包含 防止互引用
RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    ui->pass_edit->setEchoMode(QLineEdit::Password);
    ui->confirm_edit->setEchoMode(QLineEdit::Password);
    ui->err_tip->setProperty("State","normal");
    repolish(ui->err_tip);
    connect(HttpMgr::Getinstance().get(),&HttpMgr::sig_reg_mod_finish,
            this,&RegisterDialog::slot_reg_mod_finish);

}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::on_get_code_clicked()
{
    //获取ui的文本
    auto email=ui->email_edit->text();
    //正则表达式 R相当于原始字符  \w+匹配一个到多个字符 a-z A-Z 14143@qq.com
    QRegularExpression regex(R"(（\w+）(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    bool match = regex.match(email).hasMatch();
    if(match)
    {
        //send mess
    }
    else{
        showTip(tr("the address is wrong"),false);//封装shoeyip这个函数
    }
}

void RegisterDialog::slot_reg_mod_finish(ReqId id, QString &res, ErrorCodes err)
{
    if(err!=ErrorCodes::SUCCESS){
        showTip(tr(" 网络请求错误"),false);
        return;
    }
    //解析 JSON 字符串 ，res 转化为 QByteArray
    QJsonDocument jsonDoc =QJsonDocument::fromJson(res.toUtf7());
    if(jsonDoc.isNull()){
        showTip(tr(" json false"),false);
        return;
    }
    //json错误
    if(!jsonDoc.isObject()){

        showTip(tr(" json false"),false);
    }
}

void RegisterDialog::showTip(QString str,bool b_ok)
{
    if(b_ok){
        ui->err_tip->setProperty("state","normal");
    }else{
         ui->err_tip->setProperty("state","err");
    }
    ui->err_tip->setText(str);
    ui->err_tip->setProperty("statue","err");
    repolish(ui->err_tip);
}

