#!/bin/bash


#cat ./data/data_map
line=$(head -n 1 ./data/data_map)  #get first line of data_map, which is the last taken data file.
#echo $line
var=$((line+1)) #var is the new vaiable, it gets incrimented by 1.

echo Now on data $var
#mkdir "dat

echo $var > ./data/data_map

mkdir ./data/$var


#open ttyACM0at 115200, save output to a data file.
sudo minicom -C ./data/$var/jerry.csv -b 115200 -D /dev/ttyACM0


