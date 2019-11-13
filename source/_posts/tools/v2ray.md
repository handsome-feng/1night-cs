服务器端:
1. 注册域名
2. 注册cloudflare
	* Add your site
	* 添加域名解析记录，选择A记录，name填www，IPv4填写你的搬瓦工VPS的IP，云朵请点成灰色仅dns解析，先不使用CDN
	* 提示修改Nameservers，并提供了两个域名服务器地址，在你的域名注册商那修改域名服务器即可
	* SSL设置为Full
3. 安装v2ray
	* bash <(curl -s -L https://git.io/v2ray.sh)
	* 传输协议选择4:WebSocket+TLS
	* 确认域名已经解析到vps地址，然后输入正确的域名
	* v2ray url生成vmess url链接，用户配置客户端

客户端：
```shell
wget https://install.direct/go.sh
sudo bash go.sh
```

将配置文件拷贝到/etc/v2ray/config.json

```shell
sudo systemctl start v2ray
```



chromium --proxy-server="socks5://127.0.0.1:1080"