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



连接字符串：

echo "0"${k}



删除每行开头的所有空格

sed 's/^[ ]//g' test 



`find . -name "\*.c" | xargs grep -H "hello"`



watch -d -n 1 tree -L 1 /usr/share/applications