#!/bin/bash
images=(mall kiba elas logs rabb naco sent seat)
lst=$(docker ps | grep -v ID | awk  '{print  $2 }' |cut -c1-4 |uniq) 
for l in $lst
do
 if [[ "${images[@]}" =~ "${l}"  ]];then
   continue 
 else
   #echo ${l}	
   img=$(docker ps | grep "$l" | grep -v ID | awk '{print $1}')
   if [[ ${#img} -ne 0 ]];then
     docker stop ${img}
     docker rmi ${img}
     echo "stop success $l" 
     #docker stop "${l}*"
   fi
 fi
done
