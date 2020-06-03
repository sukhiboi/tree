cp binary_tree.c binary_tree.h test
cd test
rm -rf *.o
gcc -c *.c
gcc -o run_test *.o
echo "Running tests"
echo "----------------------------------------------"
./run_test
echo "\n"
rm -rf *.o
rm binary_tree.c binary_tree.h
rm run_test