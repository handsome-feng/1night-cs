

- [ ] 熟悉Python语言，掌握函数式和面向对象编程，能够编写模块化、可重用、易维护的代码；
- [ ] 掌握Nginx + Django Web开发；

### Debug

* print

* assert

* logging

* pdb

  python -m pdb hello.py

  pdb.set_trace()

和静态语言不同，Python允许对实例变量绑定任何数据，也就是说，对于两个实例变量，虽然它们都是同一个类的不同实例，但拥有的变量名称都可能不同



有些时候，你会看到以一个下划线开头的实例变量名，比如_name，这样的实例变量外部是可以访问的，但是，按照约定俗成的规定，当你看到这样的变量时，意思就是，“虽然我可以被访问，但是，请把我视为私有变量，不要随意访问”。



双下划线开头的实例变量是不是一定不能从外部访问呢？其实也不是。不能直接访问__name是因为Python解释器对外把__name变量改成了`_Student__name`，所以，仍然可以通过`_Student__name`来访问__name变量：



这就是动态语言的“鸭子类型”，它并不要求严格的继承体系，一个对象只要“看起来像鸭子，走起路来像鸭子”，那它就可以被看做是鸭子。



实例属性优先级比类属性高，因此，它会屏蔽掉类的name属性



### GIL 线程全局锁

### 多路复用

select:   1. 连接数受限; 2. fd集合从用户态拷贝到内核态; 3. 遍历所有fd，查找速度慢

poll:        改善1

epoll:



### 闭包

### 协程

#### windows下将python文件转为可执行文件：

pip install pyinstaller

pyinstaller -F foo.py



#### 鼠键模拟: PyUserInput



#### 浏览器调试： selenium



#### 浏览器UA: fake_useragent

