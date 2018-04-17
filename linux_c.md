# Linux C

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
 1. 父进程通过wait和waitpid等函数等待子进程结束，这会导致父进程挂起。
 2. 如果父进程很忙，那么可以用signal函数为SIGCHLD安装handler，因为子进程结束后， 父进程会收到该信号，可以在handler中调用wait回收。
 3. 如果父进程不关心子进程什么时候结束，那么可以用signal（SIGCHLD,SIG_IGN） 通知内核，自己对子进程的结束不感兴趣，那么子进程结束后，内核会回收， 并不再给父进程发送信号。
 4. 还有一些技巧，就是fork两次，父进程fork一个子进程，然后继续工作，子进程fork一个孙进程后退出，那么孙进程被init接管，孙进程结束后，init会回收。不过子进程的回收 还要自己做。 

### 二叉数用在什么情况
### 进程间通讯
### 察看进程占用IO命令
### 察看多线程所有线程ID
### 察看程序在执行什么系统调用


## 网络
### tcp三次握手，POST和GET请求方法的区别
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

客户端接收到服务器端的 FIN 报文后进入此状态，此时并不是直接进入 CLOSED 状态，还需要等待一个时间计时器设置的时间 2MSL。这么做有两个理由：
1. 确保最后一个确认报文段能够到达。如果 B 没收到 A 发送来的确认报文段，那么就会重新发送连接释放请求报文段，A 等待一段时间就是为了处理这种情况的发生。
2. 等待一段时间是为了让本连接持续时间内所产生的所有报文段都从网络中消失，使得下一个新的连接不会出现旧的连接请求报文段。

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
### mysql数据存储过程，B数，哈析表
### map底层

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
## 项目
### flatpak
bubblewrap uses `PR_SET_NO_NEW_PRIVS` to turn off setuid binaries, which is the [traditional way](https://en.wikipedia.org/wiki/Chroot#Limitations) to get out of things like chroots.
```
/* Never gain any more privs during exec */
  if (prctl (PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0) < 0)
```
bubblewrap works by creating a new, completely empty, mount namespace where the root is on a tmpfs that is invisible from the host, and will be automatically cleaned up when the last process exits.
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

