#!/bin/sh

echo 'Enter name of contest: '
read  name
mkdir $name
cd $name

for var
do
	mkdir $var
	cd $var
	cp "../../main.cpp" main$var.cpp
	cp "../../input.txt" $var.txt
	cd ..
done
