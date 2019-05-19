/**
 * @author João Bolsson (jvmarques@inf.ufsm.br)
 * @version 2019, May 19.
 */
#include "curl_code.h"

int main() {
    char *word = "Sport Club Internacional";

    srand(time(NULL));
    CURL *curl_handle;

    // page_content recebe o conteudo da pagina de partida: Sistema_operativo
    char *page_content = download_page(curl_handle, "https://pt.wikipedia.org/wiki/Sistema_operativo");

    printf("%s\n", page_content);

    // links_readed: variavel onde o numero de links lidos eh salvo.
    int links_readed;
    // links: lista de links lidos. A funcao find_links ira tentar ler 50
    // links dentro da pagina.
    char **links = find_links(curl_handle, page_content, 50, &links_readed);

    if (links_readed == 50) {
        // Mostra os links
        for (int i = 0; i < 50; i++) {
            printf("%d. %s\n", i, links[i]);
        }
    }

    // Sorteia um dos links para ser acessado.
    int random = rand() % links_readed;

    printf("\nLINK SORTEADO: %s\n", links[random]);

    /* we're done with libcurl, so clean it up */
    curl_global_cleanup();
    return 0;
}

