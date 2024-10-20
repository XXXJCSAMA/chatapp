#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    //点ui->regbtn is QPushButton 发出信号clicked  this（LoginDialog）接受，接受之后 发出switchRegister - mainwindow
    connect(ui->regbtn,&QPushButton::clicked,this,&LoginDialog::switchRegister);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}
