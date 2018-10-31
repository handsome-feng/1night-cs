# Linux C 进阶之路

标签（空格分隔）： linux

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
        gettimeofday(&starttime,0);
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
### gdb调试
```
$ b main            //设置断点
$ info b            //显示断点
$ delte 3           //删除断点，基于断点号
$ delete 1-3
$ clear mythrad1    //删除断点基于文件或行号
$ clear myThread.c :mythread1
$ info threads      //显示线程
$ thread 2          //切换到线程2
$ set scheduler-locking on //只调试当前线程
$ step              //单步调试，跟踪
$ bt                //查看当前所有栈信息
$ frame             //查看当前栈（当前执行的源码在哪一行）
$ info locals       //显示所有局部变量
$ print xx          //显示变量xx的值 
$ watch n           //监控n的值，有变化时显示出来
$ file /home/feng/a.out //载入新的symbol table
$ attach pid        //附到一个已经在跑的进程上(需要root权限)
$ info inferiors    //查询正在调试的进程
```
```
$ set follow-fork-mode [parent|child] set detach-on-fork [on|off]  //调试多进程
```
|follow-fork-mode | detach-on-fork | 说明 |
| --------------- | -------------- | ---- |
| parent          |  on            | 只调试主进程（GDB默认）|
| child           |  on            | 只调试子进程 |
| parent          |  off           | 同时调试两个进程，gdb跟主进程，子进程block在fork位置 |
| child           |  off           |              同时调试两个进程，gdb跟子进程，主进程block在fork位置 |

### strace
```
$ strace ./a.out    //察看程序在执行什么系统调用
$ strace -p pid     //附到一个已经在跑的进程上，实时观察
```

### 察看进程占用IO命令
只显示有I/O行为的进程　　　　　`iotop -oP`
查看特定进程　　　　　　　　　　`iotop -p $PID`
展示I/O统计,每秒更新一次　　　　`pidstat -d 1` 
查看该进程启动的完整命令行　　　`ps eho command -p $PID`
查看该进程启动时候所在的目录　　`readlink /proc/$PID/cwd`
查看该进程启动时的完整环境变量　`strings -f /proc/$PID/environ | cut -f2 -d ”`
列出该进程所打开的所有文件:　　　`lsof -p $PID`
　　cwd代表当前目录,这里是/root
　　rtd代表根目录,这里是/
　　txt代表执行的程序,这里是/bin/bash
　　mem代表映射到内存的文件,这里是/lib/libc-2.7.so等动态链接库
　　TYPE一栏表示文件/目录的类型,DIR代表目录,REG代表普通文件,CHR代表字符设备.
列出该进程所打开的网络连接:　　　`netstat -pan | grep $PID`

### 察看多线程所有线程ID
`$ ps -T`
`$ top -H -p <pid>`　　//让top输出某个特定进程并检查该进程内运行的线程状况
`$ htop`

### 定时任务
crontab
/var/spool/cron/crontabs

### 网络抓包
tcpdump   抓包
wireshark 分析抓到的包

## 数据结构
### 树
#### 二叉树用在什么情况
二叉树，本质上，是对链表和数组的一个折中
在链表中，插入、删除速度很快，但查找速度较慢。
在数组中，查找速度很快，但插入删除速度很慢。
为了解决这个问题，找寻一种能够在插入、删除、查找、遍历等操作都相对快的容器，于是人们发明了二叉树。

#### 哈希表与红黑树
咋一看，hashtable的优势是很明显的：
1. 查找、插入、删除速度都为O(1), 而红黑树的查找、插入、删除速度为O(logn). 但红黑树有很重要的特征是hashtable所不具备的：
1. 有序的特征,红黑树遍历可以得出有序输出，但hashtable是无序输出。
2. 如果需要求某一范围的输出，红黑树可以完美解决
3. hashtable的最恶劣的情况是效率很低的(比如需要resize时），而红黑树不存在这种情况。
#### 二叉搜索树

### 红黑树
set/map底层都是用红黑树实现的


## 算法
### 如何判断一个点在多边形内
### 多个字符串中如何找到前缀相同最长的两个字符串
### 堆，哈系，红黑树，哈夫曼树，二叉排序树
### 棋子走日字，从左下角到右上角，有多少走法
### 一分钟公交通过概率为p，3min呢
### mysql数据存储过程，B数，哈析表

### 如何查看单链表倒数第K个数据
设链表的长度为 N。设两个指针 P1 和 P2指向单链表头部，先让 P1 移动 K 个节点，则还有 N - K 个节点可以移动。此时让 P1 和 P2 同时移动，可以知道当 P1 移动到链表结尾时，P2 移动到 N - K 个节点处，该位置就是倒数第 K 个节点。

### 找到链表中环的入口节点
1. 找环中相汇点。分别用p1，p2指向链表头部，p1每次走一步，p2每次走二步，直到**p1==p2**找到在环中的相汇点。
2. 找环的长度。从环中的相汇点开始, p2不动, p1前移，当再次相遇时，p1刚好绕环一周,其移动即为**环的长度K**
3. 求换的起点, 转换为求环的倒数第N-K个节点，则两指针left和right均指向起始,right先走K步,然后两个指针开始同步移动,当两个指针再次相遇时,right刚好绕环一周回到起点,left则刚好走到了起点位置

### 二维数组中的查找
在一个二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。
**思路:**
从右上角开始查找。因为矩阵中的一个数，它左边的数都比它小，下边的数都比它大。因此，从右上角开始查找，就可以根据 target 和当前元素的大小关系来缩小查找区间。

复杂度：O(M+N) + O(1)

### 从尾到头打印链表
1. 使用栈
2. 使用递归(本质也是栈)
3. 使用头插法

### 斐波那契数列
动态规划

### 在O(1)时间内删除链表节点
1. 如果该节点不是尾节点，那么可以直接**将下一个节点的值赋给该节点**，令该节点指向下下个节点，然后删除下一个节点，时间复杂度为 O(1)。
2. 否则，就需要先遍历链表，找到节点的前一个节点，然后让前一个节点指向 null，时间复杂度为 O(N)。

### 设计包含min函数的栈
除了题目要求的栈之外**新开一个栈**,用来记录最小值,每当在原栈中push数据后,与最小值栈中的栈顶元素比较,如果新值较小,则在最小值栈中push新值;否则**再次push栈顶元素**.
pop的时候,只要将最小值栈也pop一下就行了.
这样,min函数只需要返回最小值栈的栈顶元素即可.
```c
public void push(int node) {
    stack.push(node);
    if (min > node) min = node;
    minStack.push(min);
}
```
**一个优化:**
一般说来,最小值不会每次都需要更新,因此最小值栈里面会有很多重复元素.因此一个简单的优化就是只在新值<=原最小值时才pushIntoMin,注意这个==的条件是不可少的,这是为了防止在pop的时候错误的pop最小值.pop的时候,只有pop值==最小值时才popMinStack, 其他时候不对最小值栈进行pop

### 从上到下打印二叉树
层序遍历直接想到的应该是基于队列实现。从上到下打印二叉树的规律：每一次打印一个结点的时候，如果该结点有子结点，则把该结点的子结点放到一个队列的末尾。接下来到队列头部取出最早进入队列的结点，重复前面的打印操作，直到队列中所有的结点都被打印出来为止。

## 网络
### Unix errno值
只要一个Unix函数中有错误发生,全局变量errno就被置为一个指明该错误类型的正值,函数本身则通常返回-1.

### 网络拓扑的发现
```
$ netstat -ni //-i提供网络接口信息,-n标志输出数值地址
$ netstat -nr // -r展示路由表
$ ifconfig    // 获取各个接口详细信息
```
找出本地网络众多主机的IP地址方法之一是针对本地接口的广播地址执行ping命令:
```
$ ping -b 192.168.255.255
```

### tcp三次握手
<div align="center"> <img src="../pics//e92d0ebc-7d46-413b-aec1-34a39602f787.png" width="600"/> </div><br>
####假设A为客户端,B为服务器端:
 1. 首先 B 处于 LISTEN（监听）状态，等待客户的连接请求.
 2. A 向 B 发送连接请求报文段，SYN=1，ACK=0，选择一个初始的序号 x.
 3. B 收到连接请求报文段，如果同意建立连接，则向A发送连接确认报文段，SYN=1，ACK=1，确认号为 x+1，同时也选择一个初始的序号 y.
 4. A 收到 B 的连接确认报文段后，还要向 B 发出确认，确认号为 y+1，序号为 x+1.
 5. B 收到 A 的确认后，连接建立。

**三次握手的原因**
第三次握手是为了防止失效的连接请求到达服务器，让服务器错误打开连接。
失效的连接请求是指，客户端发送的连接请求在网络中滞留，客户端因为没及时收到服务器端发送的连接确认，因此就重新发送了连接请求。滞留的连接请求并不是丢失，之后还是会到达服务器。如果不进行第三次握手，那么服务器会误认为客户端重新请求连接，然后打开了连接。但是并不是客户端真正打开这个连接，因此客户端不会给服务器发送数据，这个连接就白白浪费了。

### tcp四次挥手
<div align="center"> <img src="../pics//f87afe72-c2df-4c12-ac03-9b8d581a8af8.jpg" width="600"/> </div><br>
####以下描述不讨论序号和确认号，因为序号和确认号的规则比较简单。并且不讨论 ACK，因为 ACK 在连接建立之后都为1.
 1. A 发送连接释放报文段，FIN=1。
 2. B 收到之后发出确认，此时 TCP 属于半关闭状态，B 能向 A 发送数据但是 A 不能向 B 发送数据。
 3. 当 B 不再需要连接时，发送连接释放请求报文段，FIN=1。
 4. A 收到后发出确认，进入 TIME-WAIT 状态，等待 2MSL 时间后释放连接。
 5. B 收到 A 的确认后释放连接。

**四次挥手的原因**
客户端发送了 FIN 连接释放报文之后，服务器收到了这个报文，就进入了 CLOSE-WAIT 状态。这个状态是为了让服务器端发送还未传送完毕的数据，传送完毕之后，服务器会发送 FIN 连接释放报文。

**TIME_WAIT**
客户端（主动关闭的一端）接收到服务器端的 FIN 报文后进入此状态，此时并不是直接进入 CLOSED 状态，还需要等待一个时间计时器设置的时间2MSL(最长分节生命期的2倍)。每个数据报有一个称为跳限(hop limit)的8位字段，最大值为255.
这么做有两个理由：
1. 可靠地实现TCP全双工连接的终止：
假设客户端最终的ACK丢失了，服务器将重新发送最终那个FIN，因此客户端必须维护状态信息，以便重新发送最终的那个ACK。
2. 允许老的重复分节在网络中消逝：
等待一段时间是为了让本连接持续时间内所产生的所有报文段都从网络中消失，使得下一个新的连接不会出现旧的连接请求报文段。

**捎带**：服务器对客户请求的确认时伴随其应答发送的，但是如果服务器耗时大于200ms，那么我们将看到先是确认后是应答。

### SCTP
四路握手： 避免拒绝服务攻击

**端口号**
1. 0~1023    //众所周知的端口，有IANA(因特网已分配数值权威机构)分配和控制
2. 1024~49151  //已登记的端口
3. 49152～65535  //动态的或私用的(49152时65535的3/4)

标识每个端点的两个值(IP地址和端口号)通常称为一个**套接字**。

**MSS:**
最大分节大小，用户向对端TCP通告对端在每个分节中能发送的最大TCP数据量。
通常设置为： MTU - IP首部固定长度 - TCP首部固定长度

```
in_addr_r inet_addr(const char *strptr); //已废弃
```
当出错时返回INADDR_NONE常值(32位均为1的值)，所以该函数不能处理255.255.255.255

若connect失败，则该套接字不可再用，必须关闭。
**值结果参数**

### HTTP
#### POST和GET请求方法的区别
1. 参数：GET的参数以查询字符串出现在URL中，而POST的参数存储在内容尸体中。
2. 安全：安全的HTTP方法不会改变服务器的状态，是只读的，GET方法是安全的，POST不是，POST的目的是传送实体主体内容，这个内容可能是用户上传的表单数据，可能存储在服务器数据库中。
3. 幂等性：幂等的HTTP方法，同样的请求被执行一次与连续多次的效果是一样的，服务器的状态也是一样的。GET,HEAD,PUT,DELETE是幂等的，POST不是。
4. 可缓存：如果要对响应进行缓存，需要满足以下条件：
a. 请求报文的 HTTP 方法本身是可缓存的，包括 GET 和 HEAD，但是 PUT 和 DELETE 不可缓存，POST 在多数情况下不可缓存的。
b. 响应报文的状态码是可缓存的，包括：200, 203, 204, 206, 300, 301, 404, 405, 410, 414, and 501。
c. 响应报文的 Cache-Control 首部字段没有指定不进行缓存。


**fork和exec函数**
父进程中调用fork之前打开的所有描述符在fork返回后由子进程分享。子进程接着读这个已连接套接字，父进程则关闭这个已连接套接字。
进程在调用exec之前打开着的描述符通常跨exec继续保持打开，但是可以使用fcntl设置FD_CLOEXEC描述符标志禁止掉。

描述符引用计数
引用计数大于0,则close调用并不引发TCP的四分组连接终止序列。
如果确实想在TCP连接上发送一个FIN,那么可以用shutdown函数。


```
ps -a -o pid,ppid,stat,args,wchan
```

SIGKILL和SIGSTOP不能被捕获和忽略

如果一个信号在被阻塞期间产生了一次或多次，那么该信号在被解阻塞之后通常只递交一次，也就是说Unix信号默认时不排队的。

对于返回值为void的信号处理函数,依然使用return; 语句, 这样,当某个系统调用被我们编写的某个信号处理函数中断时,我们就可以得知改系统调用具体是被哪个信号处理函数的哪个return语句中断的.

当connect被一个捕获的信号中断而且不自动重启时,我们必须调用select来等待连接完成.

### 二三层交换

### select函数
maxfdp1: 是待测试的最大描述符+1
如果readset, writeset, exceptset三个指针均为空，就有了一个比Unix的sleep函数更精确的定时器。
### recv使用过程中的问题
### select最大并发量

## 数据库

## 设计模式
### 简单工厂模式

## 项目
### flatpak
基本概念：
**运行时(runtimes)**:
“运行时”提供应用程序所需的基本依赖。有各种各样的“运行时”,比如“Freedesktop运行时”，“GNOME运行时”。“Freedesktop运行时”包含一系列必要的库和服务，包括D-Bus, GLib, PulseAudio, X11和Wayland等。“GNOME运行时”基于“FreeDesktop运行时”，增加了一些GNOME平台相关的库，比如GStreamer,GTK+,GVFS等。必须针对运行时构建每个应用程序，并且必须在主机系统上安装此运行时才能运行应用程序。用户可以同时安装多个不同的运行时，包括不同版本的同一个运行时。

每一个运行时可以看做一个’/usr’ 文件系统，当程序运行时，它的运行时挂载在‘/usr’上。

**捆绑库(Bundled libraries)**
当一个程序需要的依赖不在运行时中，使用捆绑库来绑定这些依赖到程序上。

**SDK(软件开发套件)**
SDK也是一个“运行时”，是用于构建应用程序的特殊类型的运行时，它包含了构建和打包工具（‘devel’ parts），如头文件，编译器和调试器。通常，SDK与“运行时”配对，由应用程序使用。

**扩展(Extensions)**
一个扩展是对于运行时或程序的可选插件，一般用于把translations和debug信息从运行时分离出来，比如, org.freedesktop.Platform.Locale 可以追加到org.freedesktop.Platform运行时上用来添加翻译。

**沙箱（Sandbox）**
使用Flatpak，每个应用程序都是在孤立的环境中构建和运行的。默认情况下，应用程序只能“查看”自身及其“运行时”,访问用户文件，网络，graphics sockets，总线和设备上的子系统必须明确授予权限，访问其他内容（如其他进程）是不允许的。（可以通过Portals机制在沙箱内访问外面系统，比如打印，截图等）

Flatpak主要使用了如下技术：
1. bubblewrap：依赖它作为沙箱的底层实现,限制了应用程序访问操作系统或用户数据的能力，并且提供了非特权用户使用容器的能力。
2. Systemd：将各个subsystem和cgroup树关联并挂载好，为沙箱创建 cgroups。
3. D-Bus, 为应用程序提供高层APIs。
4. 使用Open Container Initiative的OCI格式作为单文件的传输格式，方便传输。
5. 使用OSTree系统用于版本化和分发文件系统树。
6. 使用Appstream元数据，使得Flatpak应用程序在软件中心可以完美呈现出来。

附：[没想到你是这样的flatpak](http://www.ubuntukylin.com/news/shownews.php?lang=cn&id=664)

**bubblewrap** uses `PR_SET_NO_NEW_PRIVS` to turn off setuid binaries, which is the [traditional way](https://en.wikipedia.org/wiki/Chroot#Limitations) to get out of things like chroots.
```
/* Never gain any more privs during exec */
  if (prctl (PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0) < 0)
```
bubblewrap works by **creating a new, completely empty, mount namespace** where the root is on a tmpfs that is invisible from the host, and will be automatically cleaned up when the last process exits.
bubblewrap always creates a new mount namespace, and the user can specify exactly what parts of the filesystem should be visible in the sandbox.
Any such directories you specify mounted `nodev` by default, and can be made readonly.

#### **namespaces**
目前，Linux内核里面实现了7种不同类型的namespace。

|名称      |  宏定义            | 隔离内容 
| :------- | :----------------- | :-------- 
| Cgroup   |   CLONE_NEWCGROUP  | Cgroup root directory (since Linux 4.6)
| IPC      |   CLONE_NEWIPC     | System V IPC, POSIX message queues (since Linux 2.6.19)
| Network  |   CLONE_NEWNET     | Network devices, stacks, ports, etc. (since Linux 2.6.24)
| Mount    |   CLONE_NEWNS      | Mount points (since Linux 2.4.19)
| PID      |   CLONE_NEWPID     |Process IDs (since Linux 2.6.24)
| User     |   CLONE_NEWUSER    | User and group IDs (started in Linux 2.6.23 and completed in Linux 3.8)
| UTS      |   CLONE_NEWUTS     | Hostname and NIS domain name (since Linux 2.6.19)

查看当前bash进程所属的namespace: `ls -l /proc/$$/ns`
namespace相关的函数:
1. clone: 创建一个新的进程并把他放到新的namespace中
```
int clone(int (*child_func)(void *), void *child_statck, int flags, void *arg);
flags: 指定一个或者多个上面的CLONE_NEW*(当然也可以包含跟namespace无关的flags),这样就会创建一个或多个新的不同类型的namespace,并新创建的子进程加入新创建的这些namespace中.
```
2. setns: 将当前进程加入到已有的namespace中
```
int setns(int fd, int nstype);
fd: 指向/proc/[pid]/ns/目录里相应namespace对应的文件,表示要加入哪个namespace
nstype: 指定nsmespace的类型:
        1. 如果当前进程不能根据fd得到它的类型,如fd由其他进程创建,并通过UNIX domain socket传给当前进程,那么就需要通过nstype来制定fd指向的namespace的类型.
        2. 如果进程能根据fd得到namespace类型,比如这个fd是由当前进程打开的,那么nstype设置为0即可.
```
3. unshare: 使当前进程退出指定类型的namespace,并加入到新创建的namespace(相当于创建并加入新的namespace)
```
int unshare(int flags);
flags: 指定一个或者多个namespace类型,这样当前进程就退出了当前指定类型的namespace并加入到新创建的namespace
```
当一个namespace中的所有进程都退出时，该namespace将会被销毁。当然还有其他方法让namespace一直存在，假设我们有一个进程号为1000的进程，以ipc namespace为例：
1. 通过mount --bind命令。例如mount --bind /proc/1000/ns/ipc /other/file，就算属于这个ipc namespace的所有进程都退出了，只要/other/file还在，这个ipc namespace就一直存在，其他进程就可以利用/other/file，通过setns函数加入到这个namespace
2. 在其他namespace的进程中打开/proc/1000/ns/ipc文件，并一直持有这个文件描述符不关闭，以后就可以用setns函数加入这个namespace。

### unity7
Compiz窗口管理器的一个插件，使用nux(opengl)图形库。部分采用cario直接绘制。
添加动态调整整体布局以及kylin style的锁屏和dash，通过监控gsettings设置，条件判断+工厂模式。

### unity8
The Unity 8 Desktop Preview is the new Unity 8 desktop shell running on the Mir display technology.
unity8(c++ + qml) + mir
If you want to run X11 applications that do not have native Mir support in the toolkit they use then the answer is an X11 server that runs on Mir. That could be either Xmir or Xwayland.

### ukui
会话管理器, 按照X 会话管理协议 (XSMP)
会话管理协议的主要部分是：
1. 会话管理器为每个客户端选择一个唯一的标识符
2. 会话管理器需要客户端保存他们的状态
3. 客户端指定它该如何重启以便恢复状态（例如，使用命令行来启动程序）

### 窗口管理器
使用窗口管理器时，Xserver 并不直接与其它 Xclient 通信，而是通过WM中转，当一些消息被定义为WM指令时，它们会被拦截。例如 Alt+F4 关闭窗口、拖动标题栏……

**系统启动过程**：
内核加载 –> init程序运行 –> systemd -> 显示管理器运行(众多服务之一) –> X Server 运行 –> 显示管理器连接到 X Server，显示登录界面 –> 用户登录后，登录界面关闭，加载桌面环境

从上面的流程可以看出，显示管理器是 X Server 的父进程，它负责启动 X Server，当 X Server 启动后，它又变成了 X Server 的一个 Client 程序，连接到 X Server 显示欢迎界面和登录界面，最后，显示管理器又是所有桌面环境的父进程，它负责启动桌面环境需要的其它 Client 程序。

lightdm 在启动 X Server 的时候，给 X Server 加上了 -nolisten tcp 参数，所以远程计算机就没有办法连接到 Ubuntu 的桌面了。

## shell脚本
```
$# 是传给脚本的参数个数
$0 是脚本本身的名字
$1 是传递给该shell脚本的第一个参数
$2 是传递给该shell脚本的第二个参数
$@ 是传给脚本的所有参数的列表
$* 是以一个单字符串显示所有向脚本传递的参数，与位置变量不同，参数可超过9个
$$ 是脚本运行的当前进程ID号
$? 是显示最后命令的退出状态，0表示没有错误，其他表示有错误
```
### 调试
bash -n scriptname
bash -v scriptname
bash -x scriptname

## git管理
git revert $id
git reset
git cherry-pick
git push origin-debain debian:master
