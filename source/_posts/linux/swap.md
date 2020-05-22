# 创建一个空文件，具体大小的话对于小内存机器建议为内存的两倍 (例子中 1K * 4M = 4 GiB).
sudo mkdir -v /var/cache/swap
cd /var/cache/swap
sudo dd if=/dev/zero of=swapfile bs=1K count=4M
sudo chmod 600 swapfile
 
# 将新建的文件转换为 swap 文件.
sudo mkswap swapfile
 
# 开启 swap.
 
sudo swapon swapfile
 
# 通过 swapon 或者 top 命令进行验证:
swapon -s
# 或者
top -bn1 | grep -i swap
# 会显示类似信息: KiB Swap: 4194300 total, 4194300 free
 
# 禁用 swap 时可以使用 sudo swapoff swapfile.
 
# 将该分区设置成开机加载.
echo "/var/cache/swap/swapfile none swap sw 0 0" | sudo tee -a /etc/fstab
 
# 测试开机加载:
sudo swapoff swapfile
sudo swapon -va
