#ifndef SINGLETON_H
#define SINGLETON_H
#include"global.h"
//c++11
template<typename T>
class Singleton{
protected:
    //希望子类继承的时候能构造 所i设置成protected: 不允许拷贝构造和拷贝复制
    Singleton()=default;
    Singleton(const Singleton<T>&)=delete;
    Singleton& operator = (const Singleton<T>& st)=delete;
    //这个实力不希望手动回收 需要一个智能指针 实例
    static std::shared_ptr<T> _instance;//咋Singleton这个类里面一个静态的成员变量
    //因为想使用时候所有的singleton都返回 static std::shared_ptr<T> _instance;
public:
    //如多写双重检测则不安全  构造可能和赋值是相反的 -定义局部的静态变量
    static std::shared_ptr<T>Getinstance(){
        static std::once_flag s_flag;//只会在函数第一次调用的时候 生成实例
        std::call_once(s_flag,[&](){
            _instance=std::shared_ptr<T>(new T);

        });
        return _instance;

    }
    void PrintAddress(){
        std::cout<<_instance.get()<<std::endl;
    }
    ~Singleton(){
        std::cout<<"this is singleton destruct"<<std::endl;
    }
};
//static std::shared_ptr<T> _instance; static变量被初始化 不是模板类 放cpp 是模板类 放在.h里
//
template<typename T>
//成员变量 初始化 为空指针
std::shared_ptr<T> Singleton<T>::_instance=nullptr;

#endif // SINGLETON_H
