#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

int main() {
    DIR *dp;
    struct dirent *ep;

    dp = opendir("./../home/estagiario");
    if (dp != NULL) {
        while ((ep = readdir(dp))) {
            puts(ep->d_name);
        }
        closedir(dp);
    } else {
        perror("Couldn't open the directory");
    }
    return 0;
}