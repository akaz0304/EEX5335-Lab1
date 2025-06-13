#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void generateFibonacci(int n) {
    int fib0 = 0, fib1 = 1, next;
    if (n >= 1) printf("%d ", fib0);
    if (n >= 2) printf("%d ", fib1);
    for (int i = 3; i <= n; i++) {
        next = fib0 + fib1;
        printf("%d ", next);
        fib0 = fib1;
        fib1 = next;
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number_of_terms>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    if (n < 0) {
        printf("Please enter a non-negative number.\n");
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        printf("Child process (PID: %d):\n", getpid());
        printf("Fibonacci sequence up to %d terms:\n", n);
        generateFibonacci(n);
    } else {
        wait(NULL);  // wait for child to finish
        printf("Parent process (PID: %d): Child completed.\n", getpid());
    }

    return 0;
}

