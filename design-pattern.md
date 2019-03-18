## 单例模式

``` python
# python装饰器实现
def Singleton(cls):
 _instance = {}
 
 def _singleton(*args, **kwargs):
  if cls not in _instance:
   _instance[cls] = cls(*args, **kwargs)
  return _instance[cls]
 
 return _singleton

@Singleton
class A(object):
 
 def __init__(self, x):
  self.x = x
```

``` c++
// c++实现
//Singleton.h
#ifndef _SINGLETON_H_
#define _SINGLETON_H_


class Singleton{
public:
	static Singleton* getInstance();

private:
	Singleton();
	//把复制构造函数和=操作符也设为私有,防止被复制
	Singleton(const Singleton&);
	Singleton& operator=(const Singleton&);

	static Singleton* instance;
};

#endif
 
// Singleton.cpp
#include "Singleton.h"


Singleton::Singleton(){
}

Singleton::Singleton(const Singleton&){
}

Singleton& Singleton::operator=(const Singleton&){
}

//在此处初始化
Singleton* Singleton::instance = new Singleton();
Singleton* Singleton::getInstance(){
	return instance;
}
 
// main.c
#include "Singleton.h"
#include <stdio.h>


int main(){
	Singleton* singleton1 = Singleton::getInstance();
	Singleton* singleton2 = Singleton::getInstance();

	if (singleton1 == singleton2)
		fprintf(stderr,"singleton1 = singleton2\n");

	return 0;
}
```

# 创建型模式

## 简单工厂模式

在简单工厂模式中，可以根据参数的不同返回不同类的实例。简单工厂模式专门定义一个类来负责创建其他类的实例，被创建的实例通常都具有共同的父类。

简单工厂模式包含如下角色：

- Factory：工厂角色

  工厂角色负责实现创建所有实例的内部逻辑

- Product：抽象产品角色

  抽象产品角色是所创建的所有对象的父类，负责描述所有实例所共有的公共接口

- ConcreteProduct：具体产品角色

  具体产品角色是创建目标，所有创建的对象都充当这个角色的某个具体类的实例。

## 抽象工厂模式

