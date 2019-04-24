#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <wait.h>
#include <time.h>

#define MAXCHAR 1000
#define TIPS_SIZE 3

void listdir(const char *name, int indent) {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(name);
    if (dir == NULL) return;

    int estado;
    pid_t idProcesso;
    while ((entry = readdir(dir))) {
        if (entry->d_type == DT_DIR) {
            char path[1024];
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;

            idProcesso = fork();
            wait(NULL);

            if (idProcesso < 0) {
                fprintf(stderr, "fork falhou\n");
                closedir(dir);
                exit(-1);
            }

            if (idProcesso == 0) { //filho
                snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);

                printf("%d [label=\"%s, %d\"];\n", getpid(), path, getpid());
                printf("%d -> %d;\n", getppid(), getpid());
//                printf("%s -> %s\n", name, path);
                listdir(path, indent + 2);
                exit(0);
//                listdir(path, indent + 2);
            }
        }
    }
//    wait(&estado);
    closedir(dir);
}

const char *getTip(char *str) {
    FILE *fp;
    char *filename = "./../banco_de_dicas.txt";

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Could not open file %s", filename);
        return NULL;
    }

    int r = rand() % TIPS_SIZE;
    int i = 0;

    while (fgets(str, MAXCHAR, fp) != NULL) {
        if (i == r) {
            break;
        }
        i++;
    }
    fclose(fp);
    return str;
}

void createTipFile(const char *dir) {
    FILE *fPtr;

    char path[1024];

    snprintf(path, sizeof(path), "%s/%s", dir, "dica_do_dia.txt");
    fPtr = fopen(path, "w");

    if (fPtr == NULL) {
        printf("Unable to create file.\n");
        exit(EXIT_FAILURE);
    }

    char str[MAXCHAR];
    const char *tip = getTip(str);

    fputs(tip, fPtr);
    fclose(fPtr);
}

int main() {
    srand((unsigned int) time(NULL));

    // exemplo para criar arquivo de dica em /home
//    createTipFile("./home");

    const char* path = "./home";

    printf("%d [label=\"%s, %d\"];\n", getpid(), path, getpid());
    listdir(path, 0);

    return 0;
}