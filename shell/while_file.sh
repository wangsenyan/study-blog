#!/bin/bash
# window文件最后一行没换行符.不能识别为一行
while read LINE || [[ -n ${LINE} ]]
do 
  NAME=`echo $LINE | awk '{print $1}'`
  AGE=`echo $LINE | awk '{print $2}'`
  SEX=`echo $LINE | awk '{print $3}'`
  echo "My name is $NAME, i'am $AGE years old, I'm a $SEX"
done < while_f.txt


