rm a.out
gcc -pthread -fsanitize=thread -Wall -Wextra -Werror *.c
./a.out 3 100 200 200 2