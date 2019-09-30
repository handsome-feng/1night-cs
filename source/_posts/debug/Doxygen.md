---
title: Doxygen + graphviz
---

## 简介

### doxygen

Doxygen is the de facto standard tool for generating documentation from annotated C++ sources, but it also supports other popular programming languages such as C, Objective-C, C#, PHP, Java, Python, IDL (Corba, Microsoft, and UNO/OpenOffice flavors), Fortran, VHDL, Tcl, and to some extent D.

### graphviz

Graphviz is open source graph visualization software. Graph visualization is a way of representing structural information as diagrams of abstract graphs and networks. It has important applications in networking, bioinformatics,  software engineering, database and web design, machine learning, and in visual interfaces for other technical domains.

## 安装

```shell
$ sudo apt install doxygen doxygen-gui grahpviz
```

## 使用

```shell
$ doxywizard
```

## 注释规则

doxygen并不能随便读取你的C++的注释,必须按照一定的规则才能生成

## 参考

https://www.jianshu.com/p/fe4b6b95dca5