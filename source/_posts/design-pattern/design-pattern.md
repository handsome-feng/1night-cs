## 设计模式的六大原则

1. 开闭原则（Open Close Principle）

开闭原则的意思是：对扩展开放，对修改关闭。在程序需要进行拓展的时候，不能去修改原有的代码，实现一个热插拔的效果。简言之，是为了使程序的扩展性好，易于维护和升级。想要达到这样的效果，我们需要使用接口和抽象类，后面的具体设计中我们会提到这点。

2. 里氏代换原则（Liskov Substitution Principle）

里氏代换原则是面向对象设计的基本原则之一。 里氏代换原则中说，任何基类可以出现的地方，子类一定可以出现。LSP 是继承复用的基石，只有当派生类可以替换掉基类，且软件单位的功能不受到影响时，基类才能真正被复用，而派生类也能够在基类的基础上增加新的行为。里氏代换原则是对开闭原则的补充。实现开闭原则的关键步骤就是抽象化，而基类与子类的继承关系就是抽象化的具体实现，所以里氏代换原则是对实现抽象化的具体步骤的规范。

3. 依赖倒转原则（Dependence Inversion Principle）

这个原则是开闭原则的基础，具体内容：针对接口编程，依赖于抽象而不依赖于具体。

4. 接口隔离原则（Interface Segregation Principle）

这个原则的意思是：使用多个隔离的接口，比使用单个接口要好。它还有另外一个意思是：降低类之间的耦合度。由此可见，其实设计模式就是从大型软件架构出发、便于升级和维护的软件设计思想，它强调降低依赖，降低耦合。

5. 迪米特法则，又称最少知道原则（Demeter Principle）

最少知道原则是指：一个实体应当尽量少地与其他实体之间发生相互作用，使得系统功能模块相对独立。

6. 合成复用原则（Composite Reuse Principle）

合成复用原则是指：尽量使用合成/聚合的方式，而不是使用继承

## 创建型模式

### 单例模式

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

### 简单工厂模式

在简单工厂模式中，可以根据参数的不同返回不同类的实例。简单工厂模式专门定义一个类来负责创建其他类的实例，被创建的实例通常都具有共同的父类。

简单工厂模式包含如下角色：

- Factory：工厂角色

  工厂角色负责实现创建所有实例的内部逻辑

- Product：抽象产品角色

  抽象产品角色是所创建的所有对象的父类，负责描述所有实例所共有的公共接口

- ConcreteProduct：具体产品角色

  具体产品角色是创建目标，所有创建的对象都充当这个角色的某个具体类的实例。

```python
class Mercedes(object):
    def __repr__(self):
        return "Mercedes-Bens"

class BMW(object):
    def __repr__(self):
        return "BMW"

# before
mercedes = Mercedes()
bmw = BMW()

# after
class SimpleFactory(object):
    def product_car(name):
        if name == 'mb':
            return Mercedes()
        elif name == 'bmw':
            return BMW()
c1 = SimpleFactory.product_car('mb')
c2 = SimpleFactory.product_car('bmw')
```

### 工厂方法模式
工厂方法模式是简单工厂的仅一步深化， 在工厂方法模式中，我们不再提供一个统一的工厂类来创建所有的对象，而是针对不同的对象提供不同的工厂。也就是说每个对象都有一个与之对应的工厂。
```python
import abc

class AbstractFactory(object):
    __metaclass__ = abc.ABMMeta

    @abc.abstractmethod
    def product_car(self):
        pass

class MercedesFactory(AbstractFactory):
    def product_car(self):
        return Mercedes()

class BMWFactory(AbstractFactory):
    def product_car(self):
        return BMW()

# before: 新增一个car，需要修改工厂的代码

# after: 新增一个car，只要增加相应的工厂
c1 = MercedesFactory().product_car()
c2 = BMWFactory().product_car()
    
```
### 抽象工厂模式
抽象工厂模式是工厂方法的进一步深化，在这个模式中的工厂类不单单可以创建一个对象，而
是可以创建一组对象。
```python
import abc

class Mercedes_C63(object):
    def __repr__(self):
        return "Mercedes-Benz: C63"

class BMW_M3(object):
    def __repr__(self):
        return "BMW: M3"

class Mercedes_G63(object):
    def __repr__(self):
        return "Mercedes_Bens: G63"

class BMW_X5(object):
    def __repr__(self):
        return "BMW: X5"

class AbstractFactory(object):
    __metaclass__ = abc.ABCMeta

    @abc.abstractmethod
    def product_car(self):
        pass

    @abc.abstractmethod
    def product_suv(self):
        pass

class MercedesFactory(AbstractFactory):
    def product_car(self):
        return Mercedes_C63()

    def product_suv(self):
        return Mercedes_G63()

class BMWFactory(AbstractFactory):
    def product_car(self):
        return BMW_M3()

    def product_suv(self):
        return BMW_X5()
```

### 建造者模式
### 原型模式

## 结构型模式
### 适配器模式
### 桥接模式
### 过滤器模式
### 组合模式
### 装饰器模式
### 外观模式
### 享元模式
### 代理模式

## 行为型模式
### 责任链模式
### 命令模式
将一个请求封装为一个对象，从而使我们可用不同的请求对客户进行参数化；对请求排队或者记录请求日志，以及支持可撤销的操作。
### 解释其模式
### 迭代器模式
### 中介者模式
用一个中介对象来封装一系列的对象交互，中介者使各对象不需要显式地相互引用，从而使其耦合松散，而且可以独立地改变它们之间的交互。
### 备忘录模式
### 观察者模式
定义对象间的一种一对多依赖关系，使得每当一个对象状态发生改变时，相关依赖对象得到通知并更新。
### 状态模式
当一个对象的内在状态改变时允许改变其行为，这个对象看起来像是改变了其类。
### 空对象模式
### 策略模式
### 模板模式
### 访问者模式
