#!/bin/bash
echo -n "Please input a score:"
read SCORE

# if [ "$SCORE" -lt 60 ]; then
#    echo "C"
# else
#    if [ "$SCORE" -lt 80 -a  "$SCORE" -gt 60 ]; then
#       echo "B"
#    else 
#      if [ "$SCORE" -ge 80 ]; then
#         echo "A"
#      fi
#    fi
# fi


if [ "$SCORE" -lt 60 ]; then
   echo "C"
elif [ "$SCORE" -lt 80 -a  "$SCORE" -gt 60 ]; then
   echo "B"
else 
   echo "A"
fi

read VAR

case $VAR in 
1) echo "BOY" ;;
2) echo "GIRL" ;;
3) echo "MID"  ;;
*) echo "BITCH" ;;
esac