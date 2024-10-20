#include"global.h"
std::function<void(QWidget*)>repolish = [](QWidget* w){
    //把旧的属性去掉加一个新的
    w->style()->unpolish(w);
    w->style()->polish(w);
};
