#!/bin/bash
FILE=/etc/notExistFile
function checkFileExist(){
  if [ -f $FILE ]; then
     return 0
  else 
     return 1
  fi 
}

echo "Call function checkFileExist"
checkFileExist
if [ $? -eq 0 ]; then 
   echo "$FILE exist"
else 
   echo "$FILE not exist"
fi