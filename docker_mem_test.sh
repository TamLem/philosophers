docker run -ti -v $(PWD):/test mem_test:0.1 bash -c "cd /test/; gcc -g -pthread *.c && valgrind ./a.out 2 800 200 200 2; \
    rm -f a.out"