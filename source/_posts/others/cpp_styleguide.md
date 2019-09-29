## 头文件

### 前置声明

尽可能避免使用前置声明。

**缺点：**

> - 前置声明隐藏了依赖关系，头文件改动时，用户的代码会跳过必要的重新编译过程。
>
> - 前置声明可能会被库的后续更改所破坏。前置声明函数或模板有时会妨碍头文件开发者变动其 API. 例如扩大形参类型，加个自带默认参数的模板形参等等。
>
> - 前置声明来自命名空间 `std::` 的 symbol 时，其行为未定义。
>
> - 很难判断什么时候该用前置声明，什么时候该用 `#include` 。极端情况下，用前置声明代替 `includes` 甚至都会暗暗地改变代码的含义：
>
>   > ```
>   > // b.h:
>   > struct B {};
>   > struct D : B {};
>   > 
>   > // good_user.cc:
>   > #include "b.h"
>   > void f(B*);
>   > void f(void*);
>   > void test(D* x) { f(x); }  // calls f(B*)
>   > ```
>
> > 如果 `#include` 被 `B` 和 `D` 的前置声明替代， `test()` 就会调用 `f(void*)` .
>
> - 前置声明了不少来自头文件的 symbol 时，就会比单单一行的 `include` 冗长。
> - 仅仅为了能前置声明而重构代码（比如用指针成员代替对象成员）会使代码变得更慢更复杂.
>
> ### 內联函数
>
> 一个较为合理的经验准则是, 不要内联超过 10 行的函数. 谨慎对待**析构函数**, 析构函数往往比其表面看起来要更长, 因为有隐含的成员和基类析构函数被调用!
>
> 另一个实用的经验准则: 内联那些包含循环或 `switch` 语句的函数常常是得不偿失 (除非在大多数情况下, 这些循环或 `switch` 语句从不被执行).
>
> 有些函数即使声明为内联的也不一定会被编译器内联, 这点很重要; 比如**虚函数**和**递归函数**就不会被正常内联. 通常, 递归函数不应该声明成内联函数.（YuleFox 注: 递归调用堆栈的展开并不像循环那么简单, 比如递归层数在编译时可能是未知的, 大多数编译器都不支持内联递归函数). 虚函数内联的主要原因则是想把它的函数体放在类定义内, 为了图个方便, 抑或是当作文档描述其行为, 比如精短的存取函数.

### #include的路径和顺序

次序如下：

* dir2/foo2.h (优先位置, 详情如下)
* C 系统文件
* C++ 系统文件
* 其他库的 .h 文件
* 本项目内 .h 文件

## 作用域

### 命名空间

內联命名空间主要用来保持跨版本的ABI兼容性

### 非成员函数、静态成员函数和全局函数

使用静态成员函数或命名空间内的非成员函数, 尽量不要用裸的全局函数. 将一系列函数直接置于命名空间中，不要用类的静态方法模拟出命名空间的效果，类的静态方法应当和类的实例或静态数据紧密相关.

### 局部变量

将函数变量尽可能置于最小作用域内, 并在变量声明时进行初始化.

C++ 允许在函数的任何位置声明变量. 我们提倡在尽可能小的作用域中声明变量, 离第一次使用越近越好. 这使得代码浏览者更容易定位变量声明的位置, 了解变量的类型和初始值. 特别是，应使用初始化的方式替代声明再赋值, 比如:

> ```
> int i;
> i = f(); // 坏——初始化和声明分离
> int j = g(); // 好——初始化时声明
> vector<int> v;
> v.push_back(1); // 用花括号初始化更好
> v.push_back(2);
> vector<int> v = {1, 2}; // 好——v 一开始就初始化
> ```

属于 `if`, `while` 和 `for` 语句的变量应当在这些语句中正常地声明，这样子这些变量的作用域就被限制在这些语句中了，举例而言:

> ```
> while (const char* p = strchr(str, '/')) str = p + 1;
> ```

Warning

有一个例外, 如果变量是一个对象, 每次进入作用域都要调用其构造函数, 每次退出作用域都要调用其析构函数. 这会导致效率降低.

```
// 低效的实现
for (int i = 0; i < 1000000; ++i) {
    Foo f;                  // 构造函数和析构函数分别调用 1000000 次!
    f.DoSomething(i);
}
```

在循环作用域外面声明这类变量要高效的多:

```
Foo f;                      // 构造函数和析构函数只调用 1 次
for (int i = 0; i < 1000000; ++i) {
    f.DoSomething(i);
}
```

### 静态和全局变量

禁止定义静态储存周期非POD变量，禁止使用含有副作用的函数初始化POD全局变量，因为多编译单元中的静态变量执行时的构造和析构顺序是未明确的，这将导致代码的不可移植。

同一个编译单元内是明确的，静态初始化优先于动态初始化，初始化顺序按照声明顺序进行，销毁则逆序。不同的编译单元之间初始化和销毁顺序属于未明确行为 (unspecified behaviour)。

## 类

### 构造函数

**优点**

- 无需考虑类是否被初始化.
- 经过构造函数完全初始化后的对象可以为 `const` 类型, 也能更方便地被标准容器或算法使用.

**缺点**

- 如果在构造函数内调用了自身的虚函数, 这类调用是不会重定向到子类的虚函数实现. 即使当前没有子类化实现, 将来仍是隐患.
- 在没有使程序崩溃 (因为并不是一个始终合适的方法) 或者使用异常 (因为已经被 [禁用](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/others/#exceptions) 了) 等方法的条件下, 构造函数很难上报错误
- 如果执行失败, 会得到一个初始化失败的对象, 这个对象有可能进入不正常的状态, 必须使用 `bool IsValid()` 或类似这样的机制才能检查出来, 然而这是一个十分容易被疏忽的方法.
- 构造函数的地址是无法被取得的, 因此, 举例来说, 由构造函数完成的工作是无法以简单的方式交给其他线程的.

**结论**

构造函数不允许调用虚函数. 如果代码允许, 直接终止程序是一个合适的处理错误的方式. 否则, 考虑用 `Init()` 方法或工厂函数.

构造函数不得调用虚函数, 或尝试报告一个非致命错误. 如果对象需要进行有意义的 (non-trivial) 初始化, 考虑使用明确的 Init() 方法或使用工厂模式. Avoid `Init()` methods on objects with no other states that affect which public methods may be called (此类形式的半构造对象有时无法正确工作).

### 隐式类型转换

在类型定义中, 类型转换运算符和单参数构造函数都应当用 `explicit` 进行标记. 一个例外是, 拷贝和移动构造函数不应当被标记为 `explicit`, 因为它们并不执行类型转换. 

### 可拷贝类型和可移动类型

如果你的类型需要, 就让它们支持拷贝 / 移动. 否则, 就把隐式产生的拷贝和移动函数禁用.

为避免拷贝构造函数, 赋值操作的滥用和编译器自动生成, 可将其声明为 `private` 且无需实现;

### 继承

所有继承必须是 `public` 的. 如果你想使用私有继承, 你应该替换成把基类的实例作为成员对象的方式.

不要过度使用实现继承. 组合常常更合适一些. 尽量做到只在 “是一个” (“is-a”, YuleFox 注: 其他 “has-a” 情况下请使用组合) 的情况下使用继承: 如果 `Bar` 的确 “是一种” `Foo`, `Bar` 才能继承 `Foo`.

必要的话, 析构函数声明为 `virtual`. 如果你的类有虚函数, 则析构函数也应该为虚函数.

对于可能被子类访问的成员函数, 不要过度使用 `protected` 关键字. 注意, 数据成员都必须是 [私有的](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/classes/#access-control).

对于重载的虚函数或虚析构函数, 使用 `override`, 或 (较不常用的) `final` 关键字显式地进行标记. 较早 (早于 C++11) 的代码可能会使用 `virtual` 关键字作为不得已的选项. 因此, 在声明重载时, 请使用 `override`, `final` 或 `virtual` 的其中之一进行标记. 标记为 `override` 或 `final` 的析构函数如果不是对基类虚函数的重载的话, 编译会报错, 这有助于捕获常见的错误. 这些标记起到了文档的作用, 因为如果省略这些关键字, 代码阅读者不得不检查所有父类, 以判断该函数是否是虚函数.

### 多重继承

只有当所有父类除第一个外都是 [纯接口类](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/classes/#interface) 时, 才允许使用多重继承. 为确保它们是纯接口, 这些类必须以 `Interface` 为后缀.

### 运算符重载

只有在意义明显, 不会出现奇怪的行为并且与对应的内建运算符的行为一致时才定义重载运算符. 例如, `|` 要作为位或或逻辑或来使用, 而不是作为 shell 中的管道.

只有对用户自己定义的类型重载运算符. 更准确地说, 将它们和它们所操作的类型定义在同一个头文件中, `.cc` 中和命名空间中. 这样做无论类型在哪里都能够使用定义的运算符, 并且最大程度上避免了多重定义的风险. 如果可能的话, 请避免将运算符定义为模板, 因为此时它们必须对任何模板参数都能够作用. 如果你定义了一个运算符, 请将其相关且有意义的运算符都进行定义, 并且保证这些定义的语义是一致的. 例如, 如果你重载了 `<`, 那么请将所有的比较运算符都进行重载, 并且保证对于同一组参数, `<` 和 `>` 不会同时返回 `true`.

建议不要将不进行修改的二元运算符定义为成员函数. 如果一个二元运算符被定义为类成员, 这时隐式转换会作用域右侧的参数却不会作用于左侧. 这时会出现 `a < b` 能够通过编译而 `b < a` 不能的情况, 这是很让人迷惑的.

不要为了避免重载操作符而走极端. 比如说, 应当定义 `==`, `=`, 和 `<<` 而不是 `Equals()`, `CopyFrom()` 和 `PrintTo()`. 反过来说, 不要只是为了满足函数库需要而去定义运算符重载. 比如说, 如果你的类型没有自然顺序, 而你要将它们存入 `std::set` 中, 最好还是定义一个自定义的比较运算符而不是重载 `<`.

不要重载 `&&`, `||`, `,` 或一元运算符 `&`. 不要重载 `operator""`, 也就是说, 不要引入用户定义字面量.

类型转换运算符在 [隐式类型转换](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/classes/#implicit-conversions) 一节有提及. `=` 运算符在 [可拷贝类型和可移动类型](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/classes/#copyable-and-movable-types) 一节有提及. 运算符 `<<` 在 [流](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/others/#streams) 一节有提及. 同时请参见 [函数重载](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/others/#function-overloading) 一节, 其中提到的的规则对运算符重载同样适用.

### 存取控制

将所有数据成员声明为private, 除非是static const类型成员.

### 声明顺序

类定义一般应以 `public:` 开始, 后跟 `protected:`, 最后是 `private:`. 省略空部分.

在各个部分中, 建议将类似的声明放在一起, 并且建议以如下的顺序: 类型 (包括 `typedef`, `using` 和嵌套的结构体与类), 常量, 工厂函数, 构造函数, 赋值运算符, 析构函数, 其它函数, 数据成员.

不要将大段的函数定义内联在类定义中. 通常，只有那些普通的, 或性能关键且短小的函数可以内联在类定义中. 

## 函数

### 参数类型

函数的参数顺序为: 输入参数在先, 后跟输出参数.

### 引用参数

函数参数列表中, 所有引用参数都必须是 `const`:

```
void Foo(const string &in, string *out);
```

事实上这在 Google Code 是一个硬性约定: 输入参数是值参或 `const` 引用, 输出参数为指针. 输入参数可以是 `const` 指针, 但决不能是非 `const` 的引用参数, 除非特殊要求, 比如 `swap()`.

有时候, 在输入形参中用 `const T*` 指针比 `const T&` 更明智. 比如:

- 可能会传递空指针.
- 函数要把指针或对地址的引用赋值给输入形参.

总而言之, 大多时候输入形参往往是 `const T&`. 若用 `const T*` 则说明输入另有处理. 所以若要使用 `const T*`, 则应给出相应的理由, 否则会使得读者感到迷惑.

### 函数重载

### 缺省参数

对于虚函数, 不允许使用缺省参数, 因为在虚函数中缺省参数不一定能正常工作. 如果在每个调用点缺省参数的值都有可能不同, 在这种情况下缺省函数也不允许使用. (例如, 不要写像 `void f(int n = counter++);` 这样的代码.)

在其他情况下, 如果缺省参数对可读性的提升远远超过了以上提及的缺点的话, 可以使用缺省参数. 如果仍有疑惑, 就使用函数重载.

## 其他C++特性

### 右值引用

### 变长数组和alloca()

优点:

> 变长数组具有浑然天成的语法. 变长数组和 `alloca()` 也都很高效.

缺点:

> 变长数组和 `alloca()` 不是标准 C++ 的组成部分. 更重要的是, 它们根据数据大小动态分配堆栈内存, 会引起难以发现的内存越界 bugs: “在我的机器上运行的好好的, 发布后却莫名其妙的挂掉了”.

结论:

> 改用更安全的分配器（allocator），就像 `std::vector` 或 `std::unique_ptr<T[]>`.
>
> ### 类型转换
>
> 定义:
>
> > C++ 采用了有别于 C 的类型转换机制, 对转换操作进行归类.
>
> 优点:
>
> > C 语言的类型转换问题在于模棱两可的操作; 有时是在做强制转换 (如 `(int)3.5`), 有时是在做类型转换 (如 `(int)"hello"`). 另外, C++ 的类型转换在查找时更醒目.
>
> 缺点:
>
> > 恶心的语法.
>
> 结论:
>
> > 不要使用 C 风格类型转换. 而应该使用 C++ 风格.
> >
> > > - 用 `static_cast` 替代 C 风格的值转换, 或某个类指针需要明确的向上转换为父类指针时.
> > > - 用 `const_cast` 去掉 `const` 限定符.
> > > - 用 `reinterpret_cast` 指针类型和整型或其它指针之间进行不安全的相互转换. 仅在你对所做一切了然于心时使用.
> >
> > 至于 `dynamic_cast` 参见 [运行时类型识别](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/others/#rtti).

### 前置自增和自减

不考虑返回值的话, 前置自增 (`++i`) 通常要比后置自增 (`i++`) 效率更高. 因为后置自增 (或自减) 需要对表达式的值 `i` 进行一次拷贝. 如果 `i` 是迭代器或其他非数值类型, 拷贝的代价是比较大的. 

对简单数值 (非对象), 两种都无所谓. 对迭代器和模板类型, 使用前置自增 (自减).

### 预处理宏

下面给出的用法模式可以避免使用宏带来的问题; 如果你要宏, 尽可能遵守:

> - 不要在 `.h` 文件中定义宏.
> - 在马上要使用时才进行 `#define`, 使用后要立即 `#undef`.
> - 不要只是对已经存在的宏使用#undef，选择一个不会冲突的名称；
> - 不要试图使用展开后会导致 C++ 构造不稳定的宏, 不然也至少要附上文档说明其行为.
> - 不要用 `##` 处理函数，类和变量的名字。

### 0, nullptr, NULL

整数用 `0`, 实数用 `0.0`, 指针用 `nullptr` 或 `NULL`, 字符 (串) 用 `'\0'`.

整数用 `0`, 实数用 `0.0`, 这一点是毫无争议的.

对于指针 (地址值), 到底是用 `0`, `NULL` 还是 `nullptr`. C++11 项目用 `nullptr`; C++03 项目则用 `NULL`, 毕竟它看起来像指针。实际上，一些 C++ 编译器对 `NULL` 的定义比较特殊，可以输出有用的警告，特别是 `sizeof(NULL)` 就和 `sizeof(0)` 不一样。

字符 (串) 用 `'\0'`, 不仅类型正确而且可读性好.

### auto

> auto 和 C++11 列表初始化的合体令人摸不着头脑：
>
> ```
> auto x(3);  // 圆括号。
> auto y{3};  // 大括号。
> ```
>
> 它们不是同一回事——`x` 是 `int`, `y` 则是 `std::initializer_list<int>`. 其它一般不可见的代理类型（acgtyrant 注：normally-invisible proxy types, 它涉及到 C++ 鲜为人知的坑：[Why is vector not a STL container?](http://stackoverflow.com/a/17794965/1546088)）也有大同小异的陷阱。
>
> 如果在接口里用 `auto`, 比如声明头文件里的一个常量，那么只要仅仅因为程序员一时修改其值而导致类型变化的话——API 要翻天覆地了。

结论：

> `auto` 只能用在局部变量里用。别用在文件作用域变量，命名空间作用域变量和类数据成员里。永远别列表初始化 `auto` 变量。
>
> `auto` 还可以和 C++11 特性「尾置返回类型（trailing return type）」一起用，不过后者只能用在 lambda 表达式里。
>
> ### 列表初始化
>
> 你可以用列表初始化。
>
> 早在 C++03 里，聚合类型（aggregate types）就已经可以被列表初始化了，比如数组和不自带构造函数的结构体：
>
> ```
> struct Point { int x; int y; };
> Point p = {1, 2};
> ```
>
> C++11 中，该特性得到进一步的推广，任何对象类型都可以被列表初始化。示范如下：
>
> ```cpp
> // Vector 接收了一个初始化列表。
> vector<string> v{"foo", "bar"};
> 
> // 不考虑细节上的微妙差别，大致上相同。
> // 您可以任选其一。
> vector<string> v = {"foo", "bar"};
> 
> // 可以配合 new 一起用。
> auto p = new vector<string>{"foo", "bar"};
> 
> // map 接收了一些 pair, 列表初始化大显神威。
> map<int, string> m = {{1, "one"}, {2, "2"}};
> 
> // 初始化列表也可以用在返回类型上的隐式转换。
> vector<int> test_function() { return {1, 2, 3}; }
> 
> // 初始化列表可迭代。
> for (int i : {-1, -2, -3}) {}
> 
> // 在函数调用里用列表初始化。
> void TestFunction2(vector<int> v) {}
> TestFunction2({1, 2, 3});
> ```
>
> 用户自定义类型也可以定义接收 `std::initializer_list<T>` 的构造函数和赋值运算符，以自动列表初始化：
>
> ```cpp
> class MyType {
>  public:
>   // std::initializer_list 专门接收 init 列表。
>   // 得以值传递。
>   MyType(std::initializer_list<int> init_list) {
>     for (int i : init_list) append(i);
>   }
>   MyType& operator=(std::initializer_list<int> init_list) {
>     clear();
>     for (int i : init_list) append(i);
>   }
> };
> MyType m{2, 3, 5, 7};
> ```
>
> 最后，列表初始化也适用于常规数据类型的构造，哪怕没有接收 `std::initializer_list<T>` 的构造函数。
>
> ```cpp
> double d{1.23};
> // MyOtherType 没有 std::initializer_list 构造函数，
>  // 直接上接收常规类型的构造函数。
> class MyOtherType {
>  public:
>   explicit MyOtherType(string);
>   MyOtherType(int, string);
> };
> MyOtherType m = {1, "b"};
> // 不过如果构造函数是显式的（explict），您就不能用 `= {}` 了。
> MyOtherType m{"b"};
> ```
>
> 千万别直接列表初始化 auto 变量，看下一句，估计没人看得懂：
>
> Warning
>
> ```cpp
> auto d = {1.23};        // d 即是 std::initializer_list<double>
> auto d = double{1.23};  // 善哉 -- d 即为 double, 并非 std::initializer_list.
> ```

### Lambda

- 按 format 小用 lambda 表达式怡情。
- 禁用默认捕获，捕获都要显式写出来。打比方，比起 `[=](int x) {return x + n;}`, 您该写成 `[n](int x) {return x + n;}` 才对，这样读者也好一眼看出 `n` 是被捕获的值。
- 匿名函数始终要简短，如果函数体超过了五行，那么还不如起名（acgtyrant 注：即把 lambda 表达式赋值给对象），或改用函数。
- 如果可读性更好，就显式写出 lambd 的尾置返回类型，就像auto.

## 命名约定

### 文件命名

文件名要全部小写, 可以包含下划线 (`_`) 或连字符 (`-`), 依照项目的约定. 如果没有约定, 那么 “`_`” 更好.

不要使用已经存在于 `/usr/include` 下的文件名

内联函数必须放在 `.h` 文件中. 如果内联函数比较短, 就直接放在 `.h` 中.

### 类型命名

**总述**

类型名称的每个单词首字母均大写, 不包含下划线: `MyExcitingClass`, `MyExcitingEnum`.

**说明**

所有类型命名 —— 类, 结构体, 类型定义 (`typedef`), 枚举, 类型模板参数 —— 均使用相同约定, 即以大写字母开始, 每个单词首字母均大写, 不包含下划线. 例如:

```cpp
// 类和结构体
class UrlTable { ...
class UrlTableTester { ...
struct UrlTableProperties { ...

// 类型定义
typedef hash_map<UrlTableProperties *, string> PropertiesMap;

// using 别名
using PropertiesMap = hash_map<UrlTableProperties *, string>;

// 枚举
enum UrlTableErrors { ...
```

### 变量命名

#### 普通变量命名

```cpp
string table_name;  // 好 - 用下划线.
string tablename;   // 好 - 全小写.

string tableName;  // 差 - 混合大小写
```

#### 类数据成员

不管是静态的还是非静态的, 类数据成员都可以和普通变量一样, 但要接下划线.

```cpp
class TableInfo {
  ...
 private:
  string table_name_;  // 好 - 后加下划线.
  string tablename_;   // 好.
  static Pool<TableInfo>* pool_;  // 好.
};
```

不管是静态的还是非静态的, 结构体数据成员都可以和普通变量一样, 不用像类那样接下划线:

```cpp
struct UrlTableProperties {
  string name;
  int num_entries;
  static Pool<UrlTableProperties>* pool;
};
```

#### 常量命名

声明为 `constexpr` 或 `const` 的变量, 或在程序运行期间其值始终保持不变的, 命名时以 “k” 开头, 大小写混合. 例如:

```
const int kDaysInAWeek = 7;
```

**说明**

所有具有静态存储类型的变量 (例如静态变量或全局变量, 参见 [存储类型](http://en.cppreference.com/w/cpp/language/storage_duration#Storage_duration)) 都应当以此方式命名. 对于其他存储类型的变量, 如自动变量等, 这条规则是可选的. 如果不采用这条规则, 就按照一般的变量命名规则.

#### 函数命名

**总述**

常规函数使用大小写混合, 取值和设值函数则要求与变量名匹配: `MyExcitingFunction()`, `MyExcitingMethod()`, `my_exciting_member_variable()`, `set_my_exciting_member_variable()`.

**说明**

一般来说, 函数名的每个单词首字母大写 (即 “驼峰变量名” 或 “帕斯卡变量名”), 没有下划线. 对于首字母缩写的单词, 更倾向于将它们视作一个单词进行首字母大写 (例如, 写作 `StartRpc()` 而非 `StartRPC()`).

```
AddTableEntry()
DeleteUrl()
OpenFileOrDie()
```

(同样的命名规则同时适用于类作用域与命名空间作用域的常量, 因为它们是作为 API 的一部分暴露对外的, 因此应当让它们看起来像是一个函数, 因为在这时, 它们实际上是一个对象而非函数的这一事实对外不过是一个无关紧要的实现细节.)

取值和设值函数的命名与变量一致. 一般来说它们的名称与实际的成员变量对应, 但并不强制要求. 例如 `int count()` 与 `void set_count(int count)`.

#### 命名空间命名

**总述**

命名空间以小写字母命名. 最高级命名空间的名字取决于项目名称. 要注意避免嵌套命名空间的名字之间和常见的顶级命名空间的名字之间发生冲突.

顶级命名空间的名称应当是项目名或者是该命名空间中的代码所属的团队的名字. 命名空间中的代码, 应当存放于和命名空间的名字匹配的文件夹或其子文件夹中.

注意 [不使用缩写作为名称](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/naming/#general-naming-rules) 的规则同样适用于命名空间. 命名空间中的代码极少需要涉及命名空间的名称, 因此没有必要在命名空间中使用缩写.

要避免嵌套的命名空间与常见的顶级命名空间发生名称冲突. 由于名称查找规则的存在, 命名空间之间的冲突完全有可能导致编译失败. 尤其是, 不要创建嵌套的 `std` 命名空间. 建议使用更独特的项目标识符 (`websearch::index`, `websearch::index_util`) 而非常见的极易发生冲突的名称 (比如 `websearch::util`).

对于 `internal` 命名空间, 要当心加入到同一 `internal` 命名空间的代码之间发生冲突 (由于内部维护人员通常来自同一团队, 因此常有可能导致冲突). 在这种情况下, 请使用文件名以使得内部名称独一无二 (例如对于 `frobber.h`, 使用 `websearch::index::frobber_internal`).

#### 枚举命名

**总述**

枚举的命名应当和 [常量](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/naming/#constant-names) 或 [宏](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/naming/#macro-names) 一致: `kEnumName` 或是 `ENUM_NAME`.

**说明**

单独的枚举值应该优先采用 [常量](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/naming/#constant-names) 的命名方式. 但 [宏](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/naming/#macro-names) 方式的命名也可以接受. 枚举名 `UrlTableErrors`(以及 `AlternateUrlTableErrors`) 是类型, 所以要用大小写混合的方式.

```
enum UrlTableErrors {
    kOK = 0,
    kErrorOutOfMemory,
    kErrorMalformedInput,
};
enum AlternateUrlTableErrors {
    OK = 0,
    OUT_OF_MEMORY = 1,
    MALFORMED_INPUT = 2,
};
```

2009 年 1 月之前, 我们一直建议采用 [宏](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/naming/#macro-names) 的方式命名枚举值. 由于枚举值和宏之间的命名冲突, 直接导致了很多问题. 由此, 这里改为优先选择常量风格的命名方式. 新代码应该尽可能优先使用常量风格. 但是老代码没必要切换到常量风格, 除非宏风格确实会产生编译期问题.

#### 宏命名

**总述**

你并不打算 [使用宏](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/others/#preprocessor-macros), 对吧? 如果你一定要用, 像这样命名: `MY_MACRO_THAT_SCARES_SMALL_CHILDREN`.

**说明**

参考 [预处理宏](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/others/#preprocessor-macros); 通常 *不应该* 使用宏. 如果不得不用, 其命名像枚举命名一样全部大写, 使用下划线:

```
#define ROUND(x) ...
#define PI_ROUNDED 3.0
```

#### 命名规则的特例

**总述**

如果你命名的实体与已有 C/C++ 实体相似, 可参考现有命名策略.

`bigopen()`: 函数名, 参照 `open()` 的形式

```
uint`: `typedef
```

`bigpos`: `struct` 或 `class`, 参照 `pos` 的形式

`sparse_hash_map`: STL 型实体; 参照 STL 命名约定

```
LONGLONG_MAX`: 常量, 如同 `INT_MAX
```

## 格式

### 函数声明与定义

**总述**

返回类型和函数名在同一行, 参数也尽量放在同一行, 如果放不下就对形参分行, 分行方式与 [函数调用](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/formatting/#function-calls) 一致.

**说明**

函数看上去像这样:

```
ReturnType ClassName::FunctionName(Type par_name1, Type par_name2) {
  DoSomething();
  ...
}
```

注意以下几点:

- 使用好的参数名.
- 只有在参数未被使用或者其用途非常明显时, 才能省略参数名.
- 如果返回类型和函数名在一行放不下, 分行.
- 如果返回类型与函数声明或定义分行了, 不要缩进.
- 左圆括号总是和函数名在同一行.
- 函数名和左圆括号间永远没有空格.
- 圆括号与参数间没有空格.
- 左大括号总在最后一个参数同一行的末尾处, 不另起新行.
- 右大括号总是单独位于函数最后一行, 或者与左大括号同一行.
- 右圆括号和左大括号间总是有一个空格.
- 所有形参应尽可能对齐.
- 缺省缩进为 4 个空格.
- 换行后的参数保持 4 个空格的缩进.

未被使用的参数如果其用途不明显的话, 在函数定义处将参数名注释起来:

```cpp
class Shape {
 public:
  virtual void Rotate(double radians) = 0;
};

class Circle : public Shape {
 public:
  void Rotate(double radians) override;
};

void Circle::Rotate(double /*radians*/) {}
// 差 - 如果将来有人要实现, 很难猜出变量的作用.
void Circle::Rotate(double) {}
```

属性, 和展开为属性的宏, 写在函数声明或定义的最前面, 即返回类型之前:

```
MUST_USE_RESULT bool IsOK();
```

### 条件语句

```cpp
if (condition) {  // 圆括号里没有空格.
  ...  // 2 空格缩进.
} else if (...) {  // else 与 if 的右括号同一行.
  ...
} else {
  ...
}
```

### 循环和开关选择

```cpp
switch (var) {
  case 0: {  // 2 空格缩进
    ...      // 4 空格缩进
    break;
  }
  case 1: {
    ...
    break;
  }
  default: {
    assert(false);
  }
}
```