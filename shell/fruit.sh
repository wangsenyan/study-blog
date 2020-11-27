#!/bin/bash
fruits="apple orange banana pear"
for FRUIT in ${fruits}
do 
  echo "$FRUIT is John's favorite"
done

echo "No more fruits"

sum=0
for VAR in {1..5}
do 
  let "sum+=VAR" #let 用于计算
done
echo "SUM IS $sum..."

sum=0
for VAR in `seq 1 100`
do
  let "sum+=VAR"
done
echo "SUM IS $sum..."

sum=0
for VAR in `seq 1 2 100` #步长为2 1 3 5
do
  let "sum+=VAR"
done
echo "SUM IS $sum..."

#for
for ((i=1; i<=10; i++))
do 
  echo -n "$i "
done
echo

for((i=1, j=100; i<=10; i++, j--))
do 
  echo "i=$i  j=$j"
done
echo

#while
#使用[[ ... ]]条件判断结构，而不是[ ... ]，能够防止脚本中的许多逻辑错误。比如，&&、||、<和> 操作符能够正常存在于[[ ]]条件判断结构中，
COUNTER=5;
while [[ $COUNTER > 0 ]]
do
  echo -n "$COUNTER"
  let "COUNTER-=1"
done
echo