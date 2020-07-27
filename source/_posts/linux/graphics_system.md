![The_Linux_Graphics_Stack_and_glamor](../pics/The_Linux_Graphics_Stack_and_glamor.svg)



Prefrence: https://www.cnblogs.com/shoemaker/p/linux_graphics01.html

List the top apps using unix sockets:
```
lsof -U +c 15 | cut -f1 -d' ' | sort | uniq -c | sort -rn | head -10
```
