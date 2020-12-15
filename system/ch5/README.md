## 调度
  - FCFS 先到先服务
  - SJF 最短作业优先
  - HRRN 最高响应比优先(highest Response Ratio Next) 
    - R=(w+s)/s w:等待时间 s:执行时间 R小先执行
  - 轮转法(RR) 
  - 多级反馈队列(Multilevel Feedback Queues)
  - 完全公平调度程序(CFS) FFS
    - 选择cpu消耗最少的进程执行,`vruntime = 实际运行时间 * 1024 / 进程权重 `
  - 
### 。。。
  - 指数平均 τn+1=αtn+(1-α)τn
  - 实时调度：
    - 单调速率调度
      调度N个进程的最坏情况下的CPU利用率为N(2^(1/N)-1)
	    1. 单个进程 100%
	    2. 两个进程 83%
	    3. 无穷大， 69%
    - 最早截止期限有限调度



### 习题
1. 为什么对调度程序而言，区分CPU约束程序和I/O约束程序很重要？



## 
- 124.64.19.88
- 122.97.178.206 江苏南京 连通

### 调度
* 页面置换算法
 - 最优页面置换算法
 - 先进先出算法(FIFO) belady
 - 最近最久未使用
 - 时钟页面置换算法
 - 二次机会法
 - 最不常用法
 - 局部置换算法--工作集模型
 - 全局置换算法
  - 工作集页置换算法 -- 主动丢页,固定窗口
  - 缺页率页面置换算法(PFF) -- 缺页率 t当前 - t上次缺页>阈值,工作集添加缺页
* 进程调度算法
  - FCFS 先到先服务
  - SJF 最短作业优先
  - HRRN 最高响应比优先(highest Response Ratio Next) 
    - R=(w+s)/s w:等待时间 s:执行时间 R小先执行
  - 轮转法(RR) 
  - 多级反馈队列(Multilevel Feedback Queues)
  - 完全公平调度程序(CFS) FFS
    - 选择cpu消耗最少的进程执行,`vruntime = 实际运行时间 * 1024 / 进程权重 `

* 磁盘调度--针对机械硬盘
  - 先进先出
  - 最短寻道时间 SSTF
  - 电梯算法 Scan
  - C-SCAN cicle
  - Clock
  - C-Clock
  - N-Step-Scan
  - FSCAN 
    - 当前所有I/O队列 SCAN
    - 新到队列 

* linux I/O调度
  - 完全公平排队I/O调度程序 CFQ
  - NOOP 电梯式调度程序
  - Dealine 截止时间调度程序
  - AS 预料I/O调度程序
  