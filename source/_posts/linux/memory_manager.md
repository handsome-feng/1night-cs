## 物理内存
### 内核使用
### slab分配器
### 进程使用
### 页缓存
## 虚拟内存
### 页表
### 驻留内存(RSS)
sudo grep Rss /proc/${pid}/smaps | awk '{sum+=$2}END{print sum}'

## 共享内存
注意：进程占用的共享内存也是计算到驻留内存中

