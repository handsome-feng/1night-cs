1.限制用户登录：

/etc/ssh/sshd_config：

AllowUsers    user1 user2@192.168.1.1              

DenyUsers    user3 user4 



2. 限制 IP登录

   通过设置 /etc/hosts.allow 和 /etc/hosts.deny 这个两个文件

   1. /etc/hosts.allow：

sshd:192.168.1.1:allow 
sshd:192.168.1.1/24:allow
	

   2. /etc/hosts.allow：

sshd:ALL # 允许全部的 ssh 登录 

hosts.allow > hosts.deny (优先级)