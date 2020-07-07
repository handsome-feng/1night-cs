基于XServer天生的网络透明性，窗口管理器不用和其它XClient运行在同一台主机上，它们只是共享同一个XServer而已，同时最基本的窗口管理器仅仅负责绘制窗口边框，包括标题条，按钮等。因此 X 架构的灵活性决定了编写窗口管理器并不是一件非常复杂的事情。窗口管理器就是一个普通的XClient。

窗口管理器 XClient 和普通的 XClient 最大的区别就是在调用 XCreateWindow() 时，需要将最后一个参数 XSetWindowAttributes *attributes 中的 Bool override_redirect 设置为真，这样以后XServer 执行其它 XClient 调用的 XCreateWindow() 请求时就会将请求重定向到设置了 override_redirect 的 XClient, 也就是窗口管理器进程，窗口管理器进程则为这个窗口创建一个父窗口，也就是边框窗口，总之正是这种机制使得窗口管理器可以“任意宰割”普通XClient创建的窗口，控制普通XClient的输入输出。也因此每个XServer任何时刻只能存在一个窗口管理器进程，因此窗口管理器在运行时需要首先检查一下XServer上是否有其它窗口管理器在运行，具体的方法是检查一下XServer中DefaultRootWindow()窗口属性是否中 override_redirect 是否被设置为真。如果已有窗口管理器在运行，那要么显示出错信息退出，要么干脆发送 kill 信号宰了它（有权限的话）。



freedesktop 已经创建了一系列规范，在设计时应尽量参考之，具体的内容可以参考 freedesktop 官方网站的具体内容，尤其需要注意窗口管理器处理 MDI 风格的规范，否则会导致使用 MDI 风格的 XClient 工作异常.



入门参考：dwm