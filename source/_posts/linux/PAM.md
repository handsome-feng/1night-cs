linux下PAM模块全称是Pluggable Authentication Module for linux（可插入式授权管理模块），该由Sun公司提供，在Linux中，PAM是可动态配置的，本地系统管理员可以自由选择应用程序如何对用户进行身份验证。PAM应用在许多程序与服务上，比如登录程序(login、su)的PAM身份验证（口令认证、限制登录），passwd强制密码，用户进程实时管理，向用户分配系统资源等。



用模块化设计和插件功能，使得我们可以轻易地在应用程序中插入新的鉴别模块或替换原先的组件,而不必对应用程序做任何修改，从而使软件的定制、维持和升级更加轻松--因为鉴别机制与应用程序之间相对独立。



PAM的配置文件位置 /etc/pam.conf,也可以在/etc/pam.d/文件夹下配置单独的文件，当存在/etc/pam.d文件夹时，Linux-PAM将会使用/etc/pam.d文件夹下的配置文件而忽略/etc/pam.conf配置文件。



service　　type 　　control　　module-path　　module-arguments

服务名称　　类型　　控制　　　　模块路径　　　　模块参数　



**type类型**



account manager(account):提供账户服务验证，如账户密码是否过期，是否对该账户提供服务



authentication manager(auth)：负责对用户进行认证并建立用户凭证；通常该模块通过交互式方法进行认证，比如你应当输入密码证明你是你，但并非所有的认证都是该类型　　



password manager(password)：进授权认证机制进行更新，如更改密码



session manager(session)：当开启一个新会话时，该模块负责处理会话的准备任务，而当关闭某一个会话时，该模块负责善后工作，如卸载该用户home目录



**control控制**



control分为简单和复杂两种语法结构，简单语法中仅有一个关键字，而复杂语法通过[ ]引入[value=action]选项



1、control简单语法包含以下值：



required：当使用此关键字的PAM模块验证失败，最终会导致PAM-API返回失败，但是会等到后续模块全部被验证后才会返回失败



requisite:该关键字与required使用方法类似，但是当PAM验证失败时，requisite会立刻向调用程序或父PAM桟返回失败值；该关键字可以防止攻击者获得系统已存在用户信息，通常该关键字用在重要的系统环境中



sufficient：如果该模块验证成功，而且该模块前无required模块验证失败，sufficient关键字将会向调用程序或者父PAM栈返回成功值而不会再调用后续的验证模块；当调用sufficient模块失败，PAM模块不会受sufficient模块失败影响，将会继续执行验证。



optional:当配置文件中仅有service+optional这一条规则时，optional模块才会起作用



include:将指定配置文件中所有的type类型作为参数包含在此控制语句中



substack:将指定配置文件中type作为参数包含在此控制语句中，和Include不同的是，在substack中完成任务或者die，只会影响substack内控制命令，不会影响完整的stack桟



2、control复杂语法



[value1=action1 value2=action2 ...]



valueN代表对应模块中控制语句的返回值，可以是下面的值：success,open_err,symbol_err,service_err,system_err,buf_err,perm_denied,deault等，其中default表示所有未被显式提到的所有值



PAM所有的错误信息列表在 /usr/include/security/_pam_types.h文件夹中



actionN可以使下列值中的某一个：

ignore:当在模块桟中使用该参数时，该模块桟的返回值不会影响应用程序获得返回值



bad:当使用bad关键字，证明模块栈的返回值代表失败；当该模块式PAM桟中第一个模块时，该模块的状态将会在整个PAM桟中使用



die:和bad关键字作用相同，当使用该动作关键时，会立刻终止模块桟，PAM会立刻返回到调用的应用程序中



ok:该动作指示将PAM的返回值直接用于所有的模块桟中，即如果前一个桟返回的状态是PAM_SUCCESS,'OK‘中的值会重写返回值；如果返回的是失败，则此'OK'的值不会重写返回值。



done：和'OK'动作基本相同，但是PAM会立刻返回到应用程序当中



reset:清空所有模块桟的状态值并以下一个模块进行验证



N：和'OK'副作用相同，但是会跳过接下来的N个模块桟，不允许使用'0'（在某些情况是使用'0'和'OK'作用类似）



四个关键字required;requisite;sufficient;optional和以下语句有相同作用



required

[success=ok new_authtok_reqd=ok ignore=ignore default=bad]



requisite

[success=ok new_authtok_reqd=ok ignore=ignore default=die]



sufficient

[success=done new_authtok_reqd=done default=ignore]



optional

[success=ok new_authtok_reqd=ok default=ignore]

**module-path**



模块路径可以使应用程序使用的PAM模块的文件名，也可是是默认模块的相对路径名：/lib/security 或者/lib64/security



**module-arguments**



模块参数是以空格作为分隔符的列表，可以用来指定PAM特殊的动作，如果需要在参数中包含空格，需要使用"[ ]",当需要在语法中使用[]时，需使用"\",如 [..[..\]..]->..[..]..；语法中的任何一个错误都会导致验证失败，而且会被记录到系统日志中