rm a.out
gcc -pthread -fsanitize=thread -Wall -Wextra -Werror *.c
./a.out 2 200 200 200 2