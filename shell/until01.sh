#!/bin/bash
sum01=0
sum02=0
i=1
# until [[ $i > 100 ]]
until [[ $i -gt 100 ]]
do 
  let "sum01+=1"
  let "j=i%2"
  if [[ $j -ne 0 ]]; then
    let "sum02+=i"
  fi
  let "i+=1"
done
echo $sum01
echo $sum02