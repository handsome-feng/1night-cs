## 数据结构

## 概述

**数据**是客观事物的符号表示，是对现实世界的事物采用计算机能够识别、存储和处理的形式进行描述的符号的集合。

**数据元素**是数据的基本单位

**数据对象**是性质相同的数据元素的集合，是数据集合的一个子集

**数据结构**的概念应包括三个方面：

* 数据元素及数据元素之间的逻辑关系，也称为数据的**逻辑结构**
* 数据元素及数据元素之间的关系在计算机中的存储表示，也称为数据的**存储结构**或物理结构
* 数据的**运算**，即对数据施加的操作

**数据类型**是一组性质相同的值的集合以及定义在这个集合上的一组操作的总称。

数据的逻辑结构分为：

* **线性结构**中有且仅有一个开始结点和一个终端结点，并且所有的结点最多只有一个前驱和一个后继。

* **非线性结构**中的一个结点可能有多个前驱和后继。

存储结构：**顺序存储**、**链接存储**、**索引存储**、**散列存储**

高级程序语言中，数据类型分为**基本类型**和**组合类型**

**抽象**：从特定的实例中抽取共同的性质形成一般化概念的过程

数据抽象

模块化

信息隐蔽

抽象数据类型：指抽象数据的组织和与之相关的操作

算法应当具有的特性：

* 输入
* 输出
* 确定性
* 有穷性
* 可行性

好的算法应满足：

* 正确性
* 可读性
* 健壮性
* 时间效率和存储占用量



## 树

### 二叉树

#### 本质

二叉树，本质上，是对链表和数组的一个折中
在链表中，插入、删除速度很快，但查找速度较慢。
在数组中，查找速度很快，但插入删除速度很慢。
为了解决这个问题，找寻一种能够在插入、删除、查找、遍历等操作都相对快的容器，于是人们发明了二叉树。

#### 二叉搜索树

若它的左子树不空，则左子树上所有结点的值均小于它的根结点的值； 若它的右子树不空，则右子树上所有结点的值均大于它的根结点的值； 它的左、右子树也分别为二叉排序树。

#### 哈夫曼树（最优二叉树）

通过某种规则（权值）来构造出一哈夫曼二叉树，在这个二叉树中，只有叶子节点才是有效的数据节点（很重要），其他的非叶子节点是为了构造出哈夫曼而引入的。

#### 红黑树

那么为了能够以较快的时间O(logN)来搜索一棵树，我们需要保证树总是平衡的（或者大部分是平衡的），也就是说每个节点的左子树节点个数和右子树节点个数尽量相等。红-黑树的就是这样的一棵平衡树，对一个要插入的数据项（删除也是），插入例程要检查会不会破坏树的特征，如果破坏了，程序就会进行纠正，根据需要改变树的结构，从而保持树的平衡。

1.每个节点不是红色就是黑色的；

2.根节点总是黑色的；

3.如果节点是红色的，则它的子节点必须是黑色的（反之不一定）,(也就是从每个叶子到根的所有路径上不能有两个连续的红色节点)；

4.从根节点到叶节点或空子节点的每条路径，必须包含相同数目的黑色节点（即相同的黑色高度）。

注意：新插入的节点颜色总是红色的，这是因为插入一个红色节点比插入一个黑色节点违背红-黑规则的可能性更小，原因是插入黑色节点总会改变黑色高度（违背规则4），但是插入红色节点只有一半的机会会违背规则3（因为父节点是黑色的没事，父节点是红色的就违背规则3）。另外违背规则3比违背规则4要更容易修正。

应用：

set/map底层都是用红黑树实现的

#### 从上到下打印二叉树

层序遍历直接想到的应该是基于队列实现。从上到下打印二叉树的规律：每一次打印一个结点的时候，如果该结点有子结点，则把该结点的子结点放到一个队列的末尾。接下来到队列头部取出最早进入队列的结点，重复前面的打印操作，直到队列中所有的结点都被打印出来为止。

#### 哈希表与红黑树

咋一看，hashtable的优势是很明显的：

1. 查找、插入、删除速度都为O(1), 而红黑树的查找、插入、删除速度为O(logn). 但红黑树有很重要的特征是hashtable所不具备的：
2. 有序的特征,红黑树遍历可以得出有序输出，但hashtable是无序输出。
3. 如果需要求某一范围的输出，红黑树可以完美解决
4. hashtable的最恶劣的情况是效率很低的(比如需要resize时），而红黑树不存在这种情况。

#### 堆

完全二叉树，除了树的最后一层节点不需要是满的，其它的每一层从左到右都是满的。

### 2-3-4树

2-3-4树每个节点最多有四个字节点和三个数据项，名字中 2,3,4 的数字含义是指一个节点可能含有的子节点的个数。对于非叶节点有三种可能的情况：

* 有一个数据项的节点总是有两个子节点；

* 有二个数据项的节点总是有三个子节点；

* 有三个数据项的节点总是有四个子节点；

简而言之，非叶节点的子节点数总是比它含有的数据项多1。如果子节点个数为L，数据项个数为D，那么：L = D + 1

* 根是child0的子树的所有子节点的关键字值小于key0；

* 根是child1的子树的所有子节点的关键字值大于key0并且小于key1；

* 根是child2的子树的所有子节点的关键字值大于key1并且小于key2；

* 根是child3的子树的所有子节点的关键字值大于key2。

### B树

应用场景：查找磁盘中的大量数据

满足：

1. 若根结点不是终端结点，则至少有2棵子树
2. 除根节点以外的所有非叶结点至少有 M/2 棵子树，至多有 M 个子树（关键字数为子树减一）
3. 所有的叶子结点都位于同一层

### B+树

满足：

1. 节点的子树数和关键字数相同（B 树是关键字数比子树数少一）
2. 节点的关键字表示的是子树中的最大数，在子树中同样含有这个数据
3. 叶子节点包含了全部数据，同时符合左小右大的顺序



## 图

### 图的存储表示

* 邻接矩阵

邻接矩阵是一个二维数组，数据项表示两点间是否存在边，如果图中有 N 个顶点，邻接矩阵就是 N*N 的数组。

* 邻接表

邻接表是一个链表数组（或者是链表的链表），每个单独的链表表示了有哪些顶点与当前顶点邻接。

* 邻接多重表

### 图的遍历

* 深度优先遍历
* 广度优先遍历

### 最小代价生成树



## 算法

### 如何判断一个点在多边形内

### 多个字符串中如何找到前缀相同最长的两个字符串

### 棋子走日字，从左下角到右上角，有多少走法

### 一分钟公交通过概率为p，3min呢

### mysql数据存储过程，B数，哈析表

### 如何查看单链表倒数第K个数据

设链表的长度为 N。设两个指针 P1 和 P2指向单链表头部，先让 P1 移动 K 个节点，则还有 N - K 个节点可以移动。此时让 P1 和 P2 同时移动，可以知道当 P1 移动到链表结尾时，P2 移动到 N - K 个节点处，该位置就是倒数第 K 个节点。

### 找到链表中环的入口节点

1. 找环中相汇点。分别用p1，p2指向链表头部，p1每次走一步，p2每次走二步，直到**p1==p2**找到在环中的相汇点。
2. 找环的长度。从环中的相汇点开始, p2不动, p1前移，当再次相遇时，p1刚好绕环一周,其移动即为**环的长度K**
3. 求换的起点, 转换为求环的倒数第N-K个节点，则两指针left和right均指向起始,right先走K步,然后两个指针开始同步移动,当两个指针再次相遇时,right刚好绕环一周回到起点,left则刚好走到了起点位置

### 二维数组中的查找

在一个二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。
**思路:**
从右上角开始查找。因为矩阵中的一个数，它左边的数都比它小，下边的数都比它大。因此，从右上角开始查找，就可以根据 target 和当前元素的大小关系来缩小查找区间。

复杂度：O(M+N) + O(1)

### 从尾到头打印链表

1. 使用栈
2. 使用递归(本质也是栈)
3. 使用头插法

### 斐波那契数列

动态规划

### 在O(1)时间内删除链表节点

1. 如果该节点不是尾节点，那么可以直接**将下一个节点的值赋给该节点**，令该节点指向下下个节点，然后删除下一个节点，时间复杂度为 O(1)。
2. 否则，就需要先遍历链表，找到节点的前一个节点，然后让前一个节点指向 null，时间复杂度为 O(N)。

### 设计包含min函数的栈

除了题目要求的栈之外**新开一个栈**,用来记录最小值,每当在原栈中push数据后,与最小值栈中的栈顶元素比较,如果新值较小,则在最小值栈中push新值;否则**再次push栈顶元素**.
pop的时候,只要将最小值栈也pop一下就行了.
这样,min函数只需要返回最小值栈的栈顶元素即可.

```c
public void push(int node) {
    stack.push(node);
    if (min > node) min = node;
    minStack.push(min);
}
```

**一个优化:**
一般说来,最小值不会每次都需要更新,因此最小值栈里面会有很多重复元素.因此一个简单的优化就是只在新值<=原最小值时才pushIntoMin,注意这个==的条件是不可少的,这是为了防止在pop的时候错误的pop最小值.pop的时候,只有pop值==最小值时才popMinStack, 其他时候不对最小值栈进行pop



## 排序算法

### 选择排序

```c++
template<typename T>
void selectionSort (T arr[], int n) {
    for (int i = 0; i < n; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[minIndex])
                minIndex = j;

        swap (arr[i], arr[minIndex]);
    }
}
```

### 插入排序

```c++
template<typename T>
void insertionSort (T arr[], int n) {
    for (int i = 1; i < n; i++) {
        // 寻找arr[i]合适的插入位置
        for (int j = i; j > 0 && arr[j] < arr[j-1]; j--) {
            swap (arr[j], arr[j-1]);  //一次交换=三次赋值
        }
    }
}
```

```c++
template<typename T>
void insertionSort2 (T arr[], int n) {
    for (int i = 1; i < n; i++) {
        T e = arr[i];
        int j; //保存元素e应该插入的位置
        for (j = i; j > 0 && arr[j-1] > e; j--) {
            arr[j] = arr[j-1]; //向后移动
        }
        arr[j] = e;
    }
}
```

对于近乎有序的数组，效率极高，近似于O(n)。

### 冒泡排序

### 合并排序

### 快速排序
