set -e
g++ -o code main.cpp
g++ -o gen gen.cpp
g++ -o brute brute.cpp
for((i = 1; ; ++i)); do
	./gen < input_file
	./code < input_file > myAnswer
	./brute < input_file > correctAnswer
	diff -Z myAnswer correctAnswer > /dev/null || break
done
echo "WA on the test:"
cat input_file
echo "My answer:"
cat myAnswer
echo "Correct answer:"
cat correctAnswer
