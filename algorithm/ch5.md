### 5.2-2
复杂度 lg(b-a),每次运行lg(b-a+1)次，都能确定结果
```c
Algorithm 1 RANDOM(a,b)
 n = dlg(b − a + 1)e
 Initialize an array A of length n
 while true do
 for i = 1 to n do
 A[i] = RANDOM(0, 1)
 end for
 if A holds the binary representation of one of the numbers in a through b then
 return number represented by A
 end if
 end while

```
### 5.2-3
利用01与10概率相同的情况
11 p^2
10 p(1-p)
01 p(1-p)
00 (1-p)^2
求和 i(1-2p(1-p))^(i-1)(2p(1-p));
结果为1/(2p(1-p)),样本次数可以为任意次数