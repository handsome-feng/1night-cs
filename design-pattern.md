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



## 抽象工厂模式

