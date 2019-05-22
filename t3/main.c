#include <stdio.h>
#include <string.h>

int main(void) {
    char *word = "dado";
    char *pageContent = "Ola tudo bem, vamos jogar dados";

    char* result = strstr(pageContent, word);

    printf("result: %s", result);
    return 0;
}