#!/bin/bash
for ((i=1; i<=100; i++))
do 
  for ((j=2; j<i; j++))
  do 
     if !(($i%$j)); then
        continue 2
     fi
  done
  echo -n "$i "
done
echo