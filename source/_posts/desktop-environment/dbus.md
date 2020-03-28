---
title: DBus
---



### Debugging





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



### dbus-daemon

https://dbus.freedesktop.org/doc/dbus-daemon.1.html

**D-Bus** is first a library that provides one-to-one communication between any two applications; 

**dbus-daemon** is an application that uses this library to implement a message bus daemon. Multiple programs connect to the message bus daemon and can exchange messages with one another.

There are two standard message bus instances: 

 systemwide message bus (installed on many systems as the "messagebus" init service) 

per-user-login-session message bus (started each time a user logs in).

SIGHUP will cause the D-Bus daemon to PARTIALLY reload its configuration file and to flush its user/group information caches. Some configuration changes would require kicking all apps off the bus; so they will only take effect if you restart the daemon. Policy changes should take effect with SIGHUP.

### configuration file

The standard systemwide and per-session message bus setups are configured in the files "/usr/share/dbus-1/system.conf" and "/usr/share/dbus-1/session.conf". These files normally <include> a system-local.conf or session-local.conf in /etc/dbus-1; you can put local overrides in those files to avoid modifying the primary configuration files.

The standard system bus normally reads additional XML files from /usr/share/dbus-1/system.d. Third-party packages should install the default policies necessary for correct operation into that directory, which has been supported since dbus 1.10 (released in 2015).

The standard system bus normally also reads XML files from /etc/dbus-1/system.d, which should be used by system administrators if they wish to override default policies.

Third-party packages would historically install XML files into /etc/dbus-1/system.d, but this practice is now considered to be deprecated: that directory should be treated as reserved for the system administrator.

* <policy>

The <policy> element defines a security policy to be applied to a particular set of connections to the bus. A policy is made up of <allow> and <deny> elements. Policies are normally used with the systemwide bus; they are analogous to a firewall in that they allow expected traffic and prevent unexpected traffic.

In general, it is best to keep system services as small, targeted programs which run in their own process and provide a single bus name. Then, all that is needed is an <allow> rule for the "own" permission to let the process claim the bus name, and a "send_destination" rule to allow traffic from some or all uids to your service.

Rules with one or more of the `send_`* family of attributes are checked in order when a connection attempts to send a message. The last rule that matches the message determines whether it may be sent. The well-known session bus normally allows sending any message. The well-known system bus normally allows sending any signal, selected method calls to the **dbus-daemon**, and exactly one reply to each previously-sent method call (either success or an error). Either of these can be overridden by configuration; on the system bus, services that will receive method calls must install configuration that allows them to do so, usually via rules of the form `<policy context="default"><allow send_destination="…"/><policy>`.



### Debugging

This is trickier, because D-Bus policy typically prevents anything but signals from being viewable by dbus-monitor. But we can change that.

1. Create a file /etc/dbus-1/system-local.conf, with these contents:
```
<!DOCTYPE busconfig PUBLIC
"-//freedesktop//DTD D-Bus Bus Configuration 1.0//EN"
"http://www.freedesktop.org/standards/dbus/1.0/busconfig.dtd">
<busconfig>
    <policy user="root">
        <allow eavesdrop="true"/>
        <allow eavesdrop="true" send_destination="*"/>
    </policy>
</busconfig>
```
2. Reboot your machine to pick up the configuration changes. Simply reloading the DBus server configuration is not sufficient. 

3. Now run dbus-monitor as root. You should be able to see all signals, method calls, and method replies.
      `sudo dbus-monitor --system`
      
4. When done debugging, it is wise to remove the policy snippet:
      `sudo rm /etc/dbus-1/system-local.conf`
      
5. Filtering all the noise
      If there is just too much information on the bus, pass a match rule like so:

      dbus-monitor "type=signal,sender='org.gnome.TypingMonitor',interface='org.gnome.TypingMonitor'"
      Multiple rules can be specified. If a message matches any of the rules, the message will be printed. Like so:

      dbus-monitor "type=error" "sender=org.freedesktop.SystemToolsBackends"

      dbus-monitor "type=method_call" "type=method_return" "type=error"
      See the [D-Bus documentation](https://dbus.freedesktop.org/doc/dbus-specification.html) for more information on match rule syntax.

#### For qt application

```
examples/dbus/remotecontrolledcar/controller/controller &
QDBUS_DEBUG=1 examples/dbus/remotecontrolledcar/car/car &
```

