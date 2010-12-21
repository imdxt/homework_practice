#!/bin/bash
# now we do "a.c"->"a"
WOKDIR=/home/peter/toy/
cd $WOKDIR
for file in `ls` 
do
    f=`echo $file|awk -F'.' '{ print  $1 }'`
    mv $file $f
done;
