##                                         内核开发特点

### 无libc库或无标准头文件

### 内核代码中所使用的C语言扩展：

* 內联函数

  `static inline void wolf(unsigned long tail_size)`

由于使用了static,编译时不会为內联函数单独建立一个函数体

* 內联汇编

  使用asm()插入汇编代码

  ```
  unsigned int log, high;
  
  asm volatile("rdtsc" : "=a" (low), "=d" (high));
  
  /* low 和 high 分别包含64位时间戳的低32位和高32位 */
  ```

  

* 分支声明

  ```
  /* 我们认为error绝大多数时间都会为0... */
  
  if (unlikely(error)) {
  
  ​    /* ... */
  
  }
  ```

  

### 没有内存保护机制

### 不要轻易在内核中使用浮点数

## 进程管理

写时拷贝：资源的复制只在需要写入的时候才进行，在此之前，以只读形式共享

fork

`clone (SIGCHLD, 0)`

vfork

`clone (CLONE_VFORK | CLONE_VM | SIGCHLD, 0);`

线程

`clone (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND, 0);`



内核线程



c语言编译器会在main()函数的返回点后面放置调用exit()的代码

终结进程大部分靠do_exit()， do_exit()永不返回

与进程相关联的所有资源被释放后，进程不可运行并处于EXIT_ZOMBIE退出状态，占用的所有内存就是**内核栈**、**thread_info**结构和**tast_struct**结构。



## 进程调度

完全公平调度算法 CFS



查看NI(nice值)

ps -el 



查看实时优先级

ps -eo state,uid,pid,ppid,rtprio,time,comm