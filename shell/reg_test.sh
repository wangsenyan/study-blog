#!/bin/bash
read -p "Give me a world: " input # -p 在尝试读取之前，输出字符串PROMPT而不带结尾的换行符
echo -en "You gave me some " # -e 启用反斜杠转义的解释 -n  不输出尾随换行符
case $input in 
  *[[:lower:]]*) echo -en "Lowercase\n " ;;
  *[[:upper:]]*) echo -en "Uppercase\n " ;;
  *[[:digit:]]*) echo -en "Numberical\n " ;;
  *) echo "Unknown input.\n" ;;
esac