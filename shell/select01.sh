#!/bin/bash
echo "Which cat do you perfer?"
select CAR in Benz Audi VolksWagen
do 
  break
done
echo "You chose $CAR"