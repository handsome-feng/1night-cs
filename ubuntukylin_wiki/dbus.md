### Debugging

examples/dbus/remotecontrolledcar/controller/controller &
QDBUS_DEBUG=1 examples/dbus/remotecontrolledcar/car/car &



### 自动启动Service

D-Bus系统提供了一种机制可以在访问某个service时，自动把应用程序运行起来。需要在/usr/share/dbus-1/services下面建立com.scorpio.test.service文件，文件的内容如下：

```
[D-BUS Service]
Name=com.scorpio.test
Exec=/path/to/scorpio/test
```



### Qt Dbus工具

* qdbusviewer

* qdbuscpp2xml

  qdbuscpp2xml会解析QObject派生类的C++头文件或是源文件，生成D-Bus的内省xml文件。qdbuscpp2xml 会区分函数的输入输出，如果参数声明为const则会是输入，否则可能会被当作输出。
  qdbuscpp2xml使用语法如下：
  `qdbuscpp2xml [options...] [files...]`
  Options参数如下：
  -p|-s|-m：只解析脚本化的属性、信号、方法（槽函数）
  -P|-S|-M：解析所有的属性、信号、方法（槽函数）
  -a：输出所有的脚本化内容，等价于-psm
  -A：输出所有的内容，等价于-PSM
  -o filename：输出内容到filename文件
  解析所有的方法输出到com.scorpio.test.xml文件命令如下：
  `qdbuscpp2xml -M test.h -o com.scorpio.test.xml`

  ```
  <!DOCTYPE node PUBLIC "-//freedesktop//DTD D-BUS Object Introspection 1.0//EN" "http://www.freedesktop.org/standards/dbus/1.0/introspect.dtd">
  <node>
    <interface name="com.scorpio.test.value">
      <method name="maxValue">
        <arg type="i" direction="out"/>
      </method>
      <method name="minValue">
        <arg type="i" direction="out"/>
      </method>
      <method name="value">
        <arg type="i" direction="out"/>
      </method>
      <method name="setValue">
        <arg name="value" type="i" direction="in"/>
      </method>
    </interface>
  </node>
  ```

* qdbusxml2cpp

  qdbusxml2cpp根据输入文件中定义的接口，生成C++实现代码。
  qdbusxml2cpp可以辅助自动生成继承于QDBusAbstractAdaptor和QDBusAbstractInterface两个类的实现代码，用于进程通信服务端和客户端，简化了开发者的代码设计。
  qdbusxml2cpp使用语法如下：
  `qdbusxml2cpp [options...] [xml-or-xml-file] [interfaces...]`
  Options参数如下：
  -a filename：输出Adaptor代码到filename
  -c classname：使用classname作为生成类的类名
  -i filename：增加#include到输出
  -l classname：当生成Adaptor代码时，使用classname作为父类
  -m：在cpp文件中包含 #include "filename.moc"语句
  -N：不使用名称空间
  -p filename：生成Proxy代码到filename文件
  解析com.scorpio.test.xml文件，生成Adaptor类ValueAdaptor，文件名称为valueAdaptor.h、valueAdaptor.cpp命令行如下：
  `qdbusxml2cpp com.scorpio.test.xml -i test.h -a valueAdaptor`
  解析com.scorpio.test.xml文件，生成Proxy类ComScorpioTestValueInterface，文件名称为testInterface.h、testInterface.cpp命令行如下：
  `qdbusxml2cpp com.scorpio.test.xml -p testInterface`