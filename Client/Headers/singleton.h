//
// Created by 86157 on 2026/3/20.
//

#ifndef CLIENT_SINGLETON_H
#define CLIENT_SINGLETON_H
#include "global.h"
//声明单例类，作为基类来使用
template <typename T>
class Singleton{
protected:
    Singleton() = default;
    //不允许拷贝构造和拷贝赋值
    Singleton(const Singleton<T>&) = delete;
    Singleton& operator = (const Singleton<T>& st) = delete;
    static std::shared_ptr<T> instance;
public:
    static std::shared_ptr<T> GetInstance(){
        static std::once_flag s_flag;
        //只有第一次调用的时候才能被初始化
        std::call_once(s_flag,[&](){
            instance = std::shared_ptr<T>(new T);
        });
        return instance;
    }

    void PrintAddress(){
        std::cout << instance.get() << std::endl;
    }

    ~Singleton(){
        std::cout << "This is singleton destruct" << std::endl;
    }
};

template <typename T>
//静态变量初始化
std::shared_ptr<T> Singleton<T>::instance = nullptr;

#endif //CLIENT_SINGLETON_H
