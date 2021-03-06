#!/bin/bash

#cat ./data/data_map
#line=$(head -n 1 ./data/data_map)  #get first line of data_map, which is the last taken data file.
#echo $line

var=$(date | sed 's/ /_/g')

echo Now on data $var
#mkdir "dat

echo $var > ./data/data_map

mkdir ./data/$var


#open ttyACM0at 115200, save output to a data file.
xterm -e minicom -C ./data/$var/tom.csv -b 57600 -D /dev/ttyUSB0 &
xterm -e minicom -C ./data/$var/jerry.csv -b 57600 -D /dev/ttyUSB1 &
#echo helloWorld


python ./python/radio_control.py



sudo killall xterm
mv timestamps.csv ./data/$var/timestamps.csv

python ./python/merge_datalogs.py ./data/$var/timestamps.csv ./data/$var/tom.csv ./data/$var/jerry.csv ./data/$var/data.csv



#python ./python/Foo.bar.py ./data/$var/tom.csv ./data/$var/jerry.csv ./data/$var/tim.csv