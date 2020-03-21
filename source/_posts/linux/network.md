---
title: Network
---



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

![三次握手](./pics/e92d0ebc-7d46-413b-aec1-34a39602f787.png)

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

![](./pics//f87afe72-c2df-4c12-ac03-9b8d581a8af8.jpg)

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



​                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     

应用层

运输层

网络层

链路层



网桥在`链路层`对网络进行互联

路由器在`网络层`对网络进行互联



5类互联网地址



`grep telnet /etc/services`



标准的服务端口号都是奇数，因为从NCP(单工，每个应用程序需要两个连接)端口号派生出来。



Internet: 世界范围内通过TCP/IP互相通信的所有主机集合

internet: 用一个共同的协议族把多个网络连接在一起





## 链路层

SLIP: 串行线路IP

缺点：

- 每一端必须知道对方的IP
- 数据帧中没有类型字段
- 没有在数据帧中加上校验和



PPP: 点对点协议



环回接口



最大传输单元MTU



路径MTU



`netstat -i`



## IP: 网际协议

使用源路由选项，IP地址可能被修改



## ARP

使用委托ARP的线索：同一个子网上的两台主机IP地址映射的硬件地址相同



## tcpdump

## ping

利用ICMP回显请求和回显报文，不用经过传输层(TCP/UDP)

## Traceroute

利用ICMP报文和IP首部中的TTL字段（生存周期），开始时，发送一个TTL字段为1的UDP数据报，然后将TTL字段每次加1，通过区分接收到的ICMP报文是超时还是端口不可达，以判断什么时候结束



### 网络抓包

tcpdump   抓包
wireshark 分析抓到的包



### ss

**ss 是 Socket Statistics 的缩写**。ss 命令可以用来获取 socket 统计信息，它显示的内容和 netstat 类似。但 ss 的优势在于它能够显示更多更详细的有关 TCP 和连接状态的信息，而且比 netstat 更快。

常用选项:

-h, --help 帮助
-V, --version  显示版本号
-t, --tcp 显示 TCP 协议的 sockets
-u, --udp 显示 UDP 协议的 sockets
-x, --unix 显示 **unix domain sockets**，与 -f 选项相同
-n, --numeric 不解析服务的名称，如 "22" 端口不会显示成 "ssh"
-l, --listening 只显示处于监听状态的端口
-p, --processes 显示监听端口的进程(Ubuntu 上需要 sudo)
-a, --all 对 TCP 协议来说，**既包含监听的端口，也包含建立的连接**
-r, --resolve 把 IP 解释为域名，把端口号解释为协议名称