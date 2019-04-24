#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <wait.h>

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
            wait(&estado);

            if (idProcesso < 0) {
                fprintf(stderr, "fork falhou\n");
                closedir(dir);
                exit(-1);
            }

            if (idProcesso == 0) { //filho
                snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);

                printf("%d -> %d;\n", getppid(), getpid());
                printf("%d [label=\"%s, %d\"];\n", getpid(), name, getpid());
                listdir(path, indent + 2);
            }
        }
    }
    closedir(dir);
}

int main() {
    listdir("./home/estagiario", 0);

    return 0;
}