#!/bin/bash
wordir=
cd $wordir
for file in `ls`
do 
f=`echo $file|awk -F'.' '{print $1}'`
echo $f
done
#***************************************
if [ -d d ]
then
rm -rf d
echo ok
fi
#********************************************
#!/bin/bash
wordir=$1
cd $wordir
for file in `ls`
do 
f=`echo $file|awk -F'.' '{print $1}'`
echo $f
done
#*********************************************
#!/bin/bash
wordir=$1
cd $wordir
for file in `ls`
do 
f=`echo $file|awk -F'.' '{print $1}'`
echo $f
done
#************************************************
