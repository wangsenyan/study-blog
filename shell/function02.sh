#!/bin/bash
function checkFileExist(){
  if [ -f $1 ]; then
    return 0
  else 
    return 1
  fi 
}

if [ $# -lt 1 ]; then
  echo "Param Blank"
  exit 1
fi

echo "Call fucntion checkFileExist"
checkFileExist $1
if [ $? -eq 0 ]; then 
   echo "$1 exist"
else 
   echo "$1 not exist"
fi 