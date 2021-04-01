## 跳跃问题

1. *[剑指 Offer 10- II. 青蛙跳台阶问题](https://leetcode-cn.com/problems/qing-wa-tiao-tai-jie-wen-ti-lcof/)*  
2. *[55. 跳跃游戏](https://leetcode-cn.com/problems/jump-game/)*  
3. *[45. 跳跃游戏 II](https://leetcode-cn.com/problems/jump-game-ii/)*  
4. *[1306. 跳跃游戏 III](https://leetcode-cn.com/problems/jump-game-iii/)*  
5. *[1345. 跳跃游戏 IV](https://leetcode-cn.com/problems/jump-game-iv/)*  
6. *[1340. 跳跃游戏 V](https://leetcode-cn.com/problems/jump-game-v/)*  
7. *[1696. 跳跃游戏 VI](https://leetcode-cn.com/problems/jump-game-vi/)*  
8. *[LCP 09 最小跳跃次数](https://leetcode-cn.com/problems/zui-xiao-tiao-yue-ci-shu/)*  
9. *[1654. 到家的最少跳跃次数](https://leetcode-cn.com/problems/minimum-jumps-to-reach-home/)*  
10. *[975. 奇偶跳](https://leetcode-cn.com/problems/odd-even-jump/)*  
11. *[403. 青蛙过河](https://leetcode-cn.com/problems/frog-jump/)*  
12. *[1377. T 秒后青蛙的位置](https://leetcode-cn.com/problems/frog-position-after-t-seconds/)*  

* 共同点,给定数组jump,jump[i]表示i位置可跳到/最大的位置

* 范围问题,可用dp,bfs,dfs,滑动窗口等解法

### 解法
1. *[剑指 Offer 10- II. 青蛙跳台阶问题](https://leetcode-cn.com/problems/qing-wa-tiao-tai-jie-wen-ti-lcof/)*  
2. *[55. 跳跃游戏](https://leetcode-cn.com/problems/jump-game/)*  
转化为,从0 到 jump[0]可达到的最大位置为i,然后从jump[0]到jump[i]最大距离
```java
class Solution {
    public boolean canJump(int[] nums) {
    int n = nums.length;
    int pre = 0;
    if(n<=1) return true;
    for(int i=0;i<n-1;i++){
        if(nums[i]==0 && pre<=i) 
            return false;
        pre = Math.max(pre,i + nums[i]);
        if(pre>=n-1)
            return true;
    }
    return false;
    }
}
```
3. *[45. 跳跃游戏 II](https://leetcode-cn.com/problems/jump-game-ii/)*  

最少跳跃次数 = 每次最大位置
```java
class Solution {
    public int jump(int[] nums) {
        int len = nums.length;
        if(len<2) return 0;
        int reach = 0;
        int next = nums[0];
        int step = 0;
        //按段来进行拆分
        for (int i = 0; i < len; i++) {
            //记录下一个最大位置
            //[0,reach] 段内最大可到达位置为 next
            //当从[reach+1,next]开始,step++
            //开始情况 reach=0,next=nums[0],step=0
            //转移 i == reach 
            //结束 next >= nums.length - 1
            next = Math.max(next,nums[i]+i);
            if(next >=len-1) return step + 1;
            if(i == reach){
                reach = next;
                step++;
            }
        }
        return step;
    }
}
```

4. *[1306. 跳跃游戏 III](https://leetcode-cn.com/problems/jump-game-iii/)*  

* 精确位置,可以通过迭代的方法,记录已经到达的位置
* 广度搜索,使用队列
```java
class Solution {
    private boolean[] seen ;
    private int[] arr;
    public boolean canReach(int[] arr, int start) {
        //从start向两边扩散
        //seen如果seen还没到,返回false
        int n = arr.length;
        seen = new boolean[n];
        this.arr = arr;
        return helper(start);
    }
    private boolean helper(int start){
        if(start<0 || start>=arr.length) return false;
        if(arr[start]==0) return true;
        else if(seen[start]) return false;
        else{
            seen[start]=true;
            return helper(start-arr[start]) || helper(start+arr[start]);
        }
    }
}
```

5. *[1345. 跳跃游戏 IV](https://leetcode-cn.com/problems/jump-game-iv/)*  

* 求最短距离,使用广度搜索
* 技巧
  - 只要被搜索,就从map中删除,后续不再被其他点遍历到

```java
class Solution {
    private Map<Integer, LinkedList<Integer>> map;
    public int minJumps(int[] arr) {
        //使用广度遍历
        map = new HashMap<>();
        int n = arr.length;
        boolean[] seen = new boolean[n];
        LinkedList<Integer> queue = new LinkedList<>();
        int step = 0;
        for (int i = 0; i < n; i++) {
            LinkedList<Integer> ls = map.getOrDefault(arr[i], new LinkedList<>());
            ls.addFirst(i);
            map.put(arr[i],ls);
        }
        queue.add(0);
        seen[0] = true;
        while(!queue.isEmpty()){
            //可加入i+1,i-1,map[i]
            int len = queue.size();
            for (int i = 0; i < len; i++) {
                Integer idx = queue.removeFirst();
                if(idx == n-1) return step;
                if(idx-1>=0 && !seen[idx-1]) {
                    queue.add(idx - 1);
                    seen[idx-1] = true;
                }
                if(idx+1<n && !seen[idx+1]) {
                    queue.add(idx + 1);
                    seen[idx+1] = true;
                }
                List<Integer> ls = map.get(arr[idx]);
                Iterator<Integer> iterator = ls.iterator();
                while (iterator.hasNext()){
                    Integer next = iterator.next();
                    if(!seen[next]){
                        queue.add(next);
                        seen[next]=true;
                        iterator.remove();
                    }
                }
            }
            step++;
        }
        return step;
    }
}
```

6. *[1340. 跳跃游戏 V](https://leetcode-cn.com/problems/jump-game-v/)*  

* 分析题意可知,高的柱形图等于范围内第二高的柱形图跳跃次数 + 1
* 动态规划?
```java
//暴力
class Solution {
    private boolean[]  ac;
    private int[] height;
    private int[] arr;
    public int maxJumps(int[] arr, int d) {
        //从最小开始
        //每个位置的最小值
        //从最小往最大
        //递归的话 f(i) = max(f(i))
        int n = arr.length;
        height = new int[n];
        ac = new boolean[n];
        this.arr = arr;
        Arrays.fill(height,1);
        int max = 1;
        for(int i=0;i<n;i++){
            max = Math.max(max,helper(i,n,d));
        }
        return max;
    }
    private int helper(int i,int n,int d){
        if(ac[i]) return height[i];
        int l = i - d > 0 ? i - d : 0;
        int r = i + d < n -1  ? i + d : n -1;
        int lmax = 0;
        int rmax = 0;
        for(int k = i -1 ;k >= l;k--){
            if(arr[k]<arr[i]){
                height[k] = helper(k,n,d);
                ac[k] = true;
                lmax = Math.max(height[k],lmax);
            }else{
                break;
            }
        }
        for(int k = i+1;k <= r;k++){
            if(arr[k]<arr[i]){
                height[k] = helper(k,n,d);
                ac[k] = true;
                rmax = Math.max(height[k],rmax);
            }else{
                break;
            }
        }
        height[i] = Math.max(lmax,rmax) + 1;
        ac[i] = true;
        return height[i];
    }
}
```

7. *[1696. 跳跃游戏 VI](https://leetcode-cn.com/problems/jump-game-vi/)*  

* 局部和最大
* 如果遇到负数,选择最大的那个,正数,加
* 得出,和为局部单调的
```java
class Solution {
    public int maxResult(int[] nums, int k) {
        //题目特点:1.局部范围与整体的协调
        //不同的想法有不同的解法
        //解法一:队列,局部最大值,如果 在[i-k,i] 寻找最大值,如果大,从队首删,否则加入队尾,
        int n = nums.length;
        LinkedList<int[]> q = new LinkedList<>();
        q.add(new int[]{nums[0],0});//[和,位置]
        int ans = nums[0];
        for (int i = 1; i < n; i++) {
            while (i - q.getFirst()[1] > k )
                q.removeFirst();
            ans = q.getFirst()[0] + nums[i];
            while (!q.isEmpty() && q.getLast()[0] <= ans){
                q.removeLast();
            }
            q.add(new int[]{ans,i});
        }
        return ans;
    }
}
```

8. *[LCP 09 最小跳跃次数](https://leetcode-cn.com/problems/zui-xiao-tiao-yue-ci-shu/)*  

* bfs

```java
class Solution {
    public int minJump(int[] jump) {
        //可以从i到【0,i+jump[i]]
        //最小次数,bfs,回边怎么办?只要经过,下次经过肯定多跳了
        int n = jump.length;
        LinkedList<Integer> queue = new LinkedList<>();
        queue.add(0);
        int step = 0;
        int mx = 1;
        while(!queue.isEmpty()){
            step++;
            int len = queue.size();
            for(int i=0;i<len;i++){
                int e = queue.removeFirst();
                if(jump[e] + e>=n) return step;
                if(jump[e] + e>=mx)
                    queue.addLast(jump[e] + e);//最远距离
                for (int j = mx ; j < e; j++) {
                    queue.add(j);
                    mx = Math.max(mx,e+1);
                }
            }
        }
        return step;
    }
}
```

9. *[1654. 到家的最少跳跃次数](https://leetcode-cn.com/problems/minimum-jumps-to-reach-home/)*  
10. *[975. 奇偶跳](https://leetcode-cn.com/problems/odd-even-jump/)*  
11. *[403. 青蛙过河](https://leetcode-cn.com/problems/frog-jump/)*  
12. *[1377. T 秒后青蛙的位置](https://leetcode-cn.com/problems/frog-position-after-t-seconds/)*  