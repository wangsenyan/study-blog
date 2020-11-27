#!/bin/bash
until [ $# -eq 0 ]
do 
    echo "Now \$l is: $1, total parameter is: $#"
    shift
done