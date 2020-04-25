
for i in A B C D /*названия папок*/
do
	mkdir $i
	echo 'Created' $i
	cd $i
	cp "../main.cpp" main.cpp
	cp "../input.txt" input.txt
	cd main.cpp
	cd ..
	
done
