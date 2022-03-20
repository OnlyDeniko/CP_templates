read name
mkdir $name
cd $name
for var
do
	mkdir $var
	cp ../template.cpp $var/${var}sol.cpp
	touch $var/in.txt
done
