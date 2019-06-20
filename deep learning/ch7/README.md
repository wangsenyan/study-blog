## <center>贝叶斯分类器</center>

### 贝叶斯决策论

* 假设有N种可能的类别标记，即 y={c1,c2,...,cN},λ<sub>ij</sub>是将一个真实标记为c<sub>j</sub>的样本误分类为c<sub>i</sub>所产生的损失。

![条件风险](../../image/con_risk.png)

* 任务：寻找一个判定准则h:X → Y 以最小化总体风险

![总体风险](../../image/exp_risk.png)

* 贝叶斯判定准则(Bayes decision rule):为最小化总体风险，只需在每个样本上选择那个能使条件风险R(c|x)最小类别标记,其中
   - h* 称为贝叶斯最优分类器，
   - 与之对应的总体风险 R(h* )称为贝叶斯风险
   - 1 - R(h* )反应了分类器所能达到的最好性能

![min_risk](../../image/min_risk.png)

* 若目标是最小化分类错误率，则误判损失 λ<sub>ij</sub>可写为

![flase_risk](../../image/flase_risk.png)

* 此时条件风险 

![条件风险](../../image/cond_risk.png)

* 最小化分类错误率的贝叶斯最优分类器为

![贝叶斯最优分类器](../../image/best_class.png)

### 极大似然估计

### 朴素贝叶斯分类器

### 半朴素贝叶斯分类器

### 贝叶斯网

### EM算法