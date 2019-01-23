# Su-write

If you find you do not have permission to perform `:w`, use the following: 

```
:w !sudo tee "%" > /dev/null
```

You can make a command so `:W` invokes sudo: 

```
command W w !sudo tee "%" > /dev/null
```

Or, if you know about the problem beforehand: 

```
sudoedit path_to_file
sudo -e path_to_file
```

# 查找

向下查找

/searchstring

向上查找

?searchstring

n N 重复上次查找

set incsearch

设置增量查找

set noincsearch

关闭增量查找

匹配以The开始的行

/^The

匹配以.结束的行

/.$

匹配任意linu开始的任意词

/linu. 

匹配以abc结束的字

\abc\>

匹配以abc开始的字

\<abc

匹配以abc开始的任意字

\abc*

匹配除abc开头外的任意字

\[^abc]

匹配任意字母和数字

/[a-aA-Z0-9]

显示当前文档及编辑信息

CTRL+G