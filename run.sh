rm -rf *.o
gcc -c *.c
gcc -o out *.o
echo "Running file"
echo "----------------------------------------------"
./out
echo "\n"
rm -rf *.o
rm out