---
title: vim
---



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



### 分屏

1. 打开文件并且分屏
    `vim -o[n] file1 [file2 ...]`
    `vim -O[n] file1 [file2 ...]`
    小写o是水平分屏,大写O是垂直分屏;中括号表示可有可无,n分屏的个数

2. 在vim中的命令模式下分屏

    a. 垂直分屏

   ```
   :vs [file2]
   ```

    垂直分屏,后面不跟文件名是将当前文件垂直分屏;跟文件名是将新文件在垂直分屏中打开(也可用 vsp或者vsplit代替vs) 

   > 快捷键操作可以不学:
   >  垂直分屏的快捷键操作为:ctrl+w v(同时按下ctrl和w键后,松开再按v键:快捷键操作只可将当前文件分屏)

b.水平分屏
 `:sv [file2]`
 水平分屏,后面不跟文件名是将当前文件水平分屏;跟文件名是将新文件在水平分屏中打开(也可用 sp或者split代替sv)

> 快捷键操作可以不学:
>  水平的快捷键操作为:ctrl+w s(同时按下ctrl和w键后,松开再按s键:快捷键操作只可将当前文件分屏)

c. 新建文件水平分屏
 `:new [newfile]`
 此命令会新建一个水平分屏
 如果跟有文件名则会新建一个文件,当写入内容并且保存退出后会新建该文件(如果没有写入内容保存退出也不会新建该文件);

> 快捷键操作可以不学:
>  新建文件水平分屏的快捷键操作为:ctrl+w n(同时按下ctrl和w键后,松开再按n键)
>  如果没有跟文件名,在写入内容后保存时命令模式下输入:
>  `:w filename`
>  会新建一个名字为filename的文件

1. 移动光标
    a. 把光标移到右边的屏中
    `ctrl+w l`
    b. 把光标移到左边的屏中
    `ctrl+w h`
    c. 把光标移到上边的屏中
    `ctrl+w k`
    d. 把光标移到下边的屏中
    `ctrl+w j`
    e. 把光标移到下一个屏中
    `ctrl+w w`
    f. 把光标移到上一个屏中
    `ctrl+w p`

2. 移动分屏
    a. 向右移动
    `ctrl+w L`
    b. 向左移动
    `ctrl+w H`
    c. 向上移动
    `ctrl+w K`
    d. 向下移动
    `ctrl+w J`
    e. 向下旋转窗口
    `ctrl+w r`
    f. 向上旋转窗口
    `ctrl+w R`
    g. 当前窗口与下一个窗口对调
    `ctrl+w x`

3. 控制分屏的尺寸
    a. 减少当前窗口高度（对上下分屏才有用）
    `ctrl+w -`        `亲测字体大小会发生变化`
    b. 增加当前窗口高度（对上下分屏才有用）
    `ctrl+w +`      `亲测字体大小会发生变化`
    c. 增加当前窗口宽度（对左右分屏才有用）
    `ctrl+w >`      `按完ctrl w 后松开,同时按下shift >`
    d. 减少当前窗口宽度（对左右分屏才有用）
    `ctrl+w <`       `按完ctrl w 后松开,同时按下shift <`
    e. 使所有窗口恢复均等
    `ctrl+w =`

4. 关闭分屏
    a. 关闭除当前分屏外的其他分屏
    `:only`
    快捷键操作

   > 快捷操作为:ctrl+w o(最后一个分屏不能用此快捷键关闭)

b. 关闭当前分屏
 \>快捷操作为:ctrl+w c (最后一个分屏不能用此快捷键关闭)

c. 关闭当前分屏
 \>快捷操作为:ctrl+w q (可用来关闭最后一个分屏)

d. 关闭所有分屏
 `:qa`