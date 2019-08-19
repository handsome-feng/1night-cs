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



批量改名:

```shell
for k in $(ls); do mv ${k} `echo ${k} | sed 's/aaa//g'`; done
```

批量替换：

sed -i "s/oldstring/newstring/g" `grep oldstring -rl yourdir`

连接字符串：

echo "0"${k}



删除每行开头的所有空格

sed 's/^[ ]//g' test 



`find . -name "\*.c" | xargs grep -H "hello"`



watch -d -n 1 tree -L 1 /usr/share/applications



### >/dev/null 2>&1

文件描述符：

| 类型                        | 文件描述符 | 默认情况               | 对应文件句柄位置 |
| :-------------------------- | :--------- | :--------------------- | :--------------- |
| 标准输入（standard input）  | 0          | 从键盘获得输入         | /proc/slef/fd/0  |
| 标准输出（standard output） | 1          | 输出到屏幕（即控制台） | /proc/slef/fd/1  |
| 错误输出（error output）    | 2          | 输出到屏幕（即控制台） | /proc/slef/fd/2  |



输出重定向：

| 命令                | 介绍                       |
| :------------------ | :------------------------- |
| command >filename   | 把标准输出重定向到新文件中 |
| command 1>filename  | 同上                       |
| command >>filename  | 把标准输出追加到文件中     |
| command 1>>filename | 同上                       |
| command 2>filename  | 把标准错误重定向到新文件中 |
| command 2>>filename | 把标准错误追加到新文件中   |



输入重定向：

| 命令                | 介绍                                          |
| :------------------ | :-------------------------------------------- |
| command <filename   | 以filename文件作为标准输入                    |
| command 0<filename  | 同上                                          |
| command <<delimiter | **从标准输入中读入，直到遇到delimiter分隔符** |



> > \>/dev/null
> >
> > 等同于： 1>/dev/null

2>&1

这里用到了重定向绑定，采用&将两个输出绑定到一起



> \>/dev/null 2>&1 VS 2>&1 >/dev/null
>
> linux在执行shell命令之前，就会确定好所有的输入输出位置，并且从左到右依次执行重定向的命令:
>
> | 命令            | 标准输出 | 错误输出 |
> | :-------------- | :------- | :------- |
> | >/dev/null 2>&1 | 丢弃     | 丢弃     |
> | 2>&1 >/dev/null | 丢弃     | 屏幕     |



\>/dev/null 2>&1 VS >/dev/null 2>/dev/null

采用后面这种写法，标准输出和错误输出会抢占往/dev/null文件的管道，所以可能会导致输出内容的时候出现缺失、覆盖等情况,可能出现乱码，也有可能出现只有error信息或者只有正常信息的情况。不管怎么说，采用这种写法，最后的情况是无法预估的。而且，由于out文件被打开了两次，两个文件描述符会抢占性的往文件中输出内容，所以整体IO效率不如`>/dev/null 2>&1`来得高。

### getopts

usage: getopts option_string variable

option_string后面跟冒号，代表选项必须带参数

option_string前面带冒号，getopts会区分invalid option和miss option argument错误。

invalid option时，varname被设为?,$OPTAGR是出问题的option;

miss option argument时，varname会被设成:,$OPTARG是出问题的option;



### eval

```shell
$ foo=10 x=foo
$ y='$'$x
$ echo $y
$foo
$ eval y='$'$x
$ echo $y
10
```

