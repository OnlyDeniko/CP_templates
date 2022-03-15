#!/bin/sh

echo 'Enter name of contest: '
read  name
mkdir $name
cd $name

for var
do
	mkdir $var
	cd $var
	cp "../../template.cpp" main.cpp
	cp "../../input.txt" input.txt
	cd ..
done
