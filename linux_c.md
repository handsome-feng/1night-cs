Linux C 进阶之路

标签（空格分隔）： linux

---
- [ ] 性能调优
- [ ] 熟练掌握STL，boost
- [ ] 设计模式
- [ ] MySQL数据库,SQL 调优
- [ ] 高并发分布式系统
- [ ] 熟悉分布式技术，如RPC、负载均衡、高可用、消息系统、缓存技术等
- [ ] 熟悉Linux系统用户层程序编写(共享内存、posix线程、信号量)
- [ ] 精通Linux系统用户层程序调试技术(gdb,strace,mtrace,ltrace)
- [ ] 熟悉socket编程，了解TCP/IP协议族；
- [ ] openstack,kvm或docker等虚拟化技术/项目开发经验的同学优先

## linux c/c++ 细节

### 常用关键字

#### volatile

**volatile**的作用是作为指令关键字，确保本条指令不会因编译器的优化而省略，且要求每次直接读值。

volatile的变量是说这变量可能会被意想不到地改变，这样，编译器就不会去假设这个变量的值了。

### 常用函数

#### sizeof & strlen

sizeof是运算符，在编译时计算，不能用来返回动态分配的内存空间的大小。

strlen是函数，运行时计算，计算字符串的长度，以0x00作为结束符。



### 浮点数如何比较
fabs(a-b)<=1E-6
### 结构体如何比较
c: 逐一比较结构体内容
c++: 重载"="运算符

### fopen参数
FILE *fopen(const char *pathname, const char *mode); Thread safety

### C++面向对象

#### 友元类：

实际上具体大概有下面两种情况需要使用友元函数：（1）运算符重载的某些场合需要使用友元。（2）两个类要共享数据的时候。

### 如何获取文件大小
1. 使用fseek, ftell:
```c
char *file = "/home/feng/time.log";

FILE *fp = fopen (file, "r"); //文件需要先读入内存, 所以效率低
if (!fp) return -1;
fseek(fp, 0L, SEEK_END);
long size = ftell(fp); //因为返回值为long, 所以超过这个大小的文件无法用这种方法
fclose(fp);
printf("%s's size: %ld\n",file, size);
```
2. 使用stat
```c
 struct stat statbuf;
 stat(file, &statbuf);
 int size2 = statbuf.st_size;
 printf("%s's size: %d\n",file, size2)
```

### setuid, setgid, strick bit
**setuid**的作用是“让执行该命令的用户以该命令拥有者的权限去执行”，比如普通用户执行passwd时会拥有root的权限，就可以修改/etc/passwd这个文件了。
**setgid**的作用是让执行文件的用户以该文件所属组的权限去执行。
**strick bit**是针对目录来说的，如果该目录设置了stick bit（粘滞位），则该目录下的文件除了该文件的创建者和root用户可以删除和修改，别的用户均不能动。
```
chmod u+s xxx  # 设置setuid权限
chmod g+s xxx  # 设置setgid权限
chmod o+t xxx  # 设置stick bit权限，针对目录
chmod 4775 xxx # 设置setuid权限
chmod 2775 xxx # 设置setgid权限
chmod 1775 xxx # 设置stick bit权限，针对目录
```
注意：有时你设置了s或t 权限，你会发现它变成了S或T，这是因为在那个位置上你没有给它x（可执行）的权限，这样的话这样的设置是不会有效的，你可以先给它赋上x的权限，然后再给s或t 的权限。

### 虚函数
### 内存对齐
**char**可起始于任意字节地址
2字节的**short**必须从偶数字节地址开始
4字节的**int**或**float**必须从能被4整除的地址开始
8字节的**long**和**double**必须从能被8整除的地址开始。
无论signed（有符号）还是unsigned（无符号）都不受影响。
x86和ARM上的基本C类型是“自对齐（self-aligned）”的。关于指针，无论32位（4字节）还是64位（8字节）也都是自对齐的。
通常情况下，**结构体实例**以其最宽的标量成员为基准进行对齐。
结构体的长度是其最宽成员长度的整数倍

1. 结构体每个成员相对于**起始地址的偏移**能够被其**自身大小整除**，如果不能则在**前一个成员后面**补充字节
2. 结构体总体大小能够**被最宽的成员的大小**整除，如不能则在**后面**补充字节

可以通过`#pragma pack x`强迫编译器采用x的对齐规则

[参考: The lost art of c structure packing](https://github.com/ludx/The-Lost-Art-of-C-Structure-Packing)

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
​        gettimeofday(&starttime,0);
　　    //do some process here
　  　  gettimeofday(&endtime,0);

### unsigned int a,b; double c=a*b 会不会溢出

### 为什么析构函数要用虚析构函数
### c的内存分布
```c
int a = 0;   /* a在全局已初始化数据区 */
char *p1;    /* p1在BSS区(未初始化全局变量) */

int main() {
    int b;   /* b在栈区 */
    char s[] = “abc”;      /* s为数组变量, 存储在栈区 */
                           /* “abc”为字符串常量, 存储在已初始化数据区 */
    char *p1, p2;          /* p1, p2在栈区 */
    char *p3 = “123456”;   /* “123456\0″已初始化在数据区, p3在栈区 */
    static int c = 0;      /* c为全局(静态)数据, 存在于已初始化数据区 */
                           /* 另外, 静态数据会自动初始化 */
    p1 = (char *)malloc(10);  /* 分配的10个字节的区域存在于堆区 */
    p2 = (char *)malloc(20);  /* 分配的数据位于堆区 */
    free(p1);
    free(p2);
}
```
**BSS(Block Started by Symblo)**
存放未初始化的全局变量和静态局部变量（程序加载时，BSS被操作系统清零）
**数据段（Data）**
存放已初始化的全局变量和静态局部变量
**数据段与BSS段区别：**
1. BSS段不占用物理文件尺寸，但占用内存空间；数据段占用物理文件，也占用内存空间。
对于大型数组如int ar0[10000] = {1, 2, 3, ...}和int ar1[10000]，ar1放在BSS段，只记录共有10000*4个字节需要初始化为0，而不是像ar0那样记录每个数据1、2、3...，此时BSS为目标文件所节省的磁盘空间相当可观。

2. 当程序读取数据段的数据时，系统会出发缺页故障，从而分配相应的物理内存；当程序读取BSS段的数据时，内核会将其转到一个全零页面，不会发生缺页故障，也不会为其分配相应的物理内存。

### 静态变量

### 僵尸进程
在fork()/execve（）过程中，假设子进程结束时父进程仍存在，而父进程fork()之前既没安装SIGCHLD信号处理函数调用waitpid()等待子进程结束，又没有显式忽略该信号，则子进程成为僵尸进程，无法正常结束。
此时即使是root身份`kill -9` 也不能杀死僵尸进程。解决大批量僵尸简单有效的办法是重起。或者杀死僵尸进程的父进程（僵尸进程的父进程必然存在），僵尸进程成为”孤儿进程”，过继给1号进程init，init始终会负责清理僵尸进程。

僵尸进程的避免：
 1. 父进程通过wait和waitpid等函数等待子进程结束，这会导致父进程挂起。
 2. 如果父进程很忙，那么可以用signal函数为SIGCHLD安装handler，因为子进程结束后， 父进程会收到该信号，可以在handler中调用wait回收。
 3. 如果父进程不关心子进程什么时候结束，那么可以用signal（SIGCHLD,SIG_IGN） 通知内核，自己对子进程的结束不感兴趣，那么子进程结束后，内核会回收， 并不再给父进程发送信号。
 4. 还有一些技巧，就是fork两次，父进程fork一个子进程，然后继续工作，子进程fork一个孙进程后退出，那么孙进程被init接管，孙进程结束后，init会回收。不过子进程的回收 还要自己做。 
```c
  /* Reap any outstanding zombies that we may have inherited */
  while (waitpid (-1, &status, WNOHANG) > 0)
    ;
```
### 线程
从 Linux 内核的角度来说，其实它并没有线程的概念。Linux 把所有线程都当做进程来实现，它将线程和进程不加区分的统一到了task_struct中。线程仅仅被视为一个与其他进程共享某些资源的进程，，而是否共享地址空间几乎是进程和 Linux 中所谓线程的唯一区别。线程创建的时候，加上了 CLONE_VM 标记，这样 线程的内存描述符 将直接指向 父进程的内存描述符。

### 线程与进程区别
1. 进程是资源分配的基本单位，线程是程序执行的最小单位，或者说cpu调度的最小单位。
2. 进程有独立的地址空间，而一个进程中的线程之间共享大部分数据，使用相同的地址空间，线程拥有自己的局部变量和堆栈（注意不是堆）。

同一进程内的所有线程共享：
* 全局变量
* 进程指令
* 大多数数据
* 打开的文件（即描述符）
* 信号处理函数和信号处置
* 当前工作目录
* 用户ID和组ID
  但是有各自的：
* 线程ID
* 寄存器集合，包括程序计数器和栈指针
* 栈（用于存放局部变量和返回地址）
* errno
* 信号掩码
* 优先级

互斥锁
条件变量

并发

竞态

死锁

互斥锁

自旋锁

读写自旋锁

顺序锁

RCU

信号量

中断屏蔽

原子操作

### 进程间通讯
#### pipe
#### eventfd
https://www.jianshu.com/p/57cc1d7d354f
eventfd类似于管道的概念，可以实现线程间的事件通知，类似于pipe。而eventfd 是一个比 pipe 更高效的线程间事件通知机制，一方面它比 pipe 少用一个 file descriper，节省了资源；另一方面，eventfd的缓冲区管理也简单得多，全部“buffer”一共只有8字节，不像pipe那样可能有不定长的真正buffer。
eventfd的缓冲区大小是sizeof(uint64_t)也就是8字节，它是一个64位的计数器，写入递增计数器，读取将得到计数器的值，并且清零。
#### 信号
```
int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
```
调用函数sigprocmask可以检测或更改其信号屏蔽字

while (waitpid (-1, &status, WNOHANG) > 0)


## 操作系统
### 内核态与用户态
用户态的应用程序访问内核态的资源：
 * 系统调用
 * 库函数
 * Shell脚本

用户态切换到内核态的3中方式：
* 系统调用 （软中断，int 80h）
* 异常
当CPU在执行运行在用户态下的程序时，发生了某些事先不可知的异常，这时会触发由当前运行进程切换到处理此异常的内核相关程序中，也就转到了内核态，比如缺页异常。
* 外围设备的中断
当外围设备完成用户请求的操作后，会向CPU发出相应的中断信号，这时CPU会暂停执行下一条即将要执行的指令转而去执行与中断信号对应的处理程序，如果先前执行的指令是用户态下的程序，那么这个转换的过程自然也就发生了由用户态到内核态的切换。比如硬盘读写操作完成，系统会切换到硬盘读写的中断处理程序中执行后续操作等

## 系统命令


### 定时任务
crontab
/var/spool/cron/crontabs
