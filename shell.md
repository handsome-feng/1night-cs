批量改名:
```shell
for k in $(ls); do mv ${k} `echo ${k} | sed 's/aaa//g'`; done
```



连接字符串：

echo "0"${k}



删除每行开头的所有空格

sed 's/^[ ]//g' test 