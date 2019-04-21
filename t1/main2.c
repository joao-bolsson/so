#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

int main() {
    pid_t idProc1, idProc2, idProc3;
    int estado, estado1, estado2;

    idProc1 = fork();
    wait(&estado);
    idProc2 = fork();
    wait(&estado1);
    idProc3 = fork();
    wait(&estado2);

    if (idProc1 < 0) {
        fprintf(stderr, "fork 3 falhou\n");
        return -1;
    } else if (idProc1 == 0) {
        printf("sou o FILHO, meu id = %d, meu pai eh %d\n", getpid(), getppid());
    } else {
        printf("sou o PAI, meu id = %d, meu pai eh %d\n", getpid(), getppid());
    }

    if (idProc2 < 0) {
        fprintf(stderr, "fork 3 falhou\n");
        return -1;
    } else if (idProc2 == 0) {
        printf("sou o FILHO, meu id = %d, meu pai eh %d\n", getpid(), getppid());
    } else {
        printf("sou o PAI, meu id = %d, meu pai eh %d\n", getpid(), getppid());
    }

    if (idProc3 < 0) {
        fprintf(stderr, "fork 3 falhou\n");
        return -1;
    } else if (idProc3 == 0) {
        printf("sou o FILHO, meu id = %d, meu pai eh %d\n", getpid(), getppid());
    } else {
        printf("sou o PAI, meu id = %d, meu pai eh %d\n", getpid(), getppid());
    }

    return 0;
}