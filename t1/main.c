#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

int main() {
    int estado;
    pid_t idProcesso;

    idProcesso = fork();
    wait(&estado);

    if (idProcesso < 0) {
        fprintf(stderr, "fork falhou\n");
        exit(-1);
    } else if (idProcesso == 0) {
        printf("sou o FILHO, meu id = %d, meu pai eh %d\n", getpid(), getppid());
    } else {
        printf("sou o PAI, meu id = %d, meu pai eh %d\n", getpid(), getppid());
    }

    int estado2;
    idProcesso = fork();
    wait(&estado2);
    if (idProcesso < 0) {
        fprintf(stderr, "fork falhou\n");
        return -1;
    } else if (idProcesso == 0) {
        printf("sou o FILHO, meu id = %d, meu pai eh %d\n", getpid(), getppid());
    } else {
        printf("sou o PAI, meu id = %d, meu pai eh %d\n", getpid(), getppid());
    }

    int estado3;
    idProcesso = fork();
    wait(&estado3);
    if (idProcesso < 0) {
        fprintf(stderr, "fork falhou\n");
        exit(-1);
    } else if (idProcesso == 0) {
        printf("sou o FILHO, meu id = %d, meu pai eh %d\n", getpid(), getppid());
    } else {
        printf("sou o PAI, meu id = %d, meu pai eh %d\n", getpid(), getppid());
    }

    return 0;
}