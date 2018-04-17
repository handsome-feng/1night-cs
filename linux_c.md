# linux c

标签（空格分隔）：面试 

---
## linux c/c++ 细节
### 浮点数如何比较
fabs(a-b)<=1E-6
### 结构体如何比较
c: 逐一比较结构体内容
c++: 重载"="运算符

### fopen参数
FILE *fopen(const char *pathname, const char *mode); Thread safety

### 如何获取文件大小
```c
fopen (file, "r");
fseek(fp, 0L, SEEK_END);
long size = ftell(fp);
```

```c
struct stat statbuf;
stat(file, &statbuf);
int size2 = statbuf.st_size;
```
### 虚函数
### 数据对齐，如何让他不对齐
`#pragma pack 1`

### malloc、free与new、delete区别
| Feature |new/delete | malloc/free |
| ------  | --------- | ----------- |
| Memory allocated from | 'Free Store'| 'Heap' |
| Returns | Fully typed pointer | void* |
| On failure | Throws (never returns NULL) | Returns NULL |
| Required size | Calculated by compiler | Must be specified in bytes |
| Handling arrays | Has an explicit version | Requires manual calculations |
| Reallocating | Not handled intuitively | Simple (no copy constructor) |
| Call of reverse | Implementation defined | No |
| Low memory cases | Can add a new memory allocator | Not handled by user code |
| Overridable | Yes | No |
| Use of (con-)/destructor | Yes | No |

### delete和delete[]区别
对于内置类型，new[]<->delete[] 怎么对应都不会有问题，free 只需要一个首地址，通过指针偏移可以获取到下一个内存块和上一个内存的地址，把这个内存块从链表中删除就 ok 了。
对于类对象数组，赋值过程中编译器做了一些 free 层面不知道的偏移，所以一旦 new[] 和 delete[] 不对应，会发生崩溃。

### 拷贝构造函数
当对对象进行拷贝时不是做简单的对象的值的拷贝而应该将堆中的数据也进行拷贝，这种拷贝模式叫做深拷贝

### 在linux下写计时器
秒级别： clock()     //c语言库函数
毫秒级：timeval starttime,endtime;
        gettimeofday(&starttime,0);
　　    //do some process here
　  　  gettimeofday(&endtime,0);
　  　
### unsigned int a,b; double c=a*b 会不会溢出

### 为什么析构函数要用虚析构函数
### c的内存分布
### 静态变量
### 进程，线程
### 僵尸进程，系统为什么不直接回收
僵尸进程的避免：
⒈ 父进程通过wait和waitpid等函数等待子进程结束，这会导致父进程挂起。
2.如果父进程很忙，那么可以用signal函数为SIGCHLD安装handler，因为子进程结束后， 父进程会收到该信号，可以在handler中调用wait回收。
⒊ 如果父进程不关心子进程什么时候结束，那么可以用signal（SIGCHLD,SIG_IGN） 通知内核，自己对子进程的结束不感兴趣，那么子进程结束后，内核会回收， 并不再给父进程发送信号。
⒋ 还有一些技巧，就是fork两次，父进程fork一个子进程，然后继续工作，子进程fork一个孙进程后退出，那么孙进程被init接管，孙进程结束后，init会回收。不过子进程的回收 还要自己做。
### 如何查看单链表倒数第K个数据
### 二叉数用在什么情况
### 进程间通讯
### 察看进程占用IO命令
### 察看多线程所有线程ID
### 察看程序在执行什么系统调用


## 网络
### tcp三次握手，POST和GET请求方法的区别，四次挥手
<div align="center"> <img src="../pics//e92d0ebc-7d46-413b-aec1-34a39602f787.png" width="600"/> </div><br>
假设A为客户端,B为服务器端:
 1. 首先 B 处于 LISTEN（监听）状态，等待客户的连接请求.
 2. A 向 B 发送连接请求报文段，SYN=1，ACK=0，选择一个初始的序号 x.
 3. B 收到连接请求报文段，如果同意建立连接，则向A发送连接确认报文段，SYN=1，ACK=1，确认号为 x+1，同时也选择一个初始的序号 y.
 4. A 收到 B 的连接确认报文段后，还要向 B 发出确认，确认号为 y+1，序号为 x+1.
 5. B 收到 A 的确认后，连接建立。


### 二三层交换
### select函数参数
### recv使用过程中的问题
### select最大并发量

## 算法
### 如何判断一个点在多边形内
### 多个字符串中如何找到前缀相同最长的两个字符串
### 堆，哈系，红黑树，哈夫曼树，二叉排序树
### 棋子走日字，从左下角到右上角，有多少走法
### 一分钟公交通过概率为p，3min呢
### 斐波那契数列
### mysql数据存储过程，B数，哈析表
### map底层

## 项目
### flatpak
bubblewrap uses `PR_SET_NO_NEW_PRIVS` to turn off setuid binaries, which is the [traditional way](https://en.wikipedia.org/wiki/Chroot#Limitations) to get out of things like chroots.
bubblewrap works by creating a new, completely empty, mount namespace where the root is on a tmpfs that is invisible from the host, and will be automatically cleaned up when the last process exits.
bubblewrap always creates a new mount namespace, and the user can specify exactly what parts of the filesystem should be visible in the sandbox.
Any such directories you specify mounted `nodev` by default, and can be made readonly.



