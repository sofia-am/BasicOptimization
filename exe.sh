gcc -Wall -pedantic -Werror -Wextra -Wconversion -std=gnu11 -pg -no-pie -fno-builtin lab3.c -o lab3
./lab3
gprof lab3 gmon.out > gprof_analysis.txt