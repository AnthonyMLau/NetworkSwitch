#!/bin/bash

# This script exports all pins and sets output to 1 (high)
# Or it unexports all pins and sets output to 0 (low)
# 1 to export, 0 to unexport

echo "1 to export, 0 to unexport"
read value

cd /sys/class/gpio
for (( i = 380; i < 550; i++))
do
    # export or unexport
    if [ $counter -eq 1 ];
    then
        echo $i | sudo tee export
    else
        echo $i | sudo tee unexport
    fi

    # check if command was successful
    if [[ $? -eq 0 && value -eq 1 ]]; 
    then
        echo ENABLE $i
        echo "out" | sudo tee gpio$i/direction
        echo 1 | sudo tee gpio$i/value
    fi
    if [[ $? -eq 0 && value -eq 0 ]];
        echo DISABLE $if
        echo 0 | sudo tee gpio$i/value
    fi

done
printf "\n"