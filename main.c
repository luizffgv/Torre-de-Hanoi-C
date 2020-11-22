// github.com/luizffgv

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hanoi.h"
#include "list.h"

int main(void)
{
    List *nomes_lista = ListNew();

    char nome_buf[64];
    fputs("Nomes dos monges (uma palavra cada): ", stdout);
    while (1)
    {
        int ch = getchar();
        if (ch == '\n')
            break;

        else
            ungetc(ch, stdin);
        scanf("%s", nome_buf);

        char *nome = malloc(strlen(nome_buf) + 1);
        strcpy(nome, nome_buf);
        ListAppend(&nomes_lista, nome);
    }

    char *nomes[ListSize(nomes_lista)];
    for (size_t nome_i = 0; nome_i < ListSize(nomes_lista); ++nome_i)
        nomes[nome_i] = ListGet(nomes_lista, nome_i);

    int ndiscos;
    fputs("Discos: ", stdout);
    do
        scanf("%d", &ndiscos);
    while (ndiscos <= 0);

    int delay_ms;
    fputs("Delay por jogada (ms): ", stdout);
    do
        scanf("%d", &delay_ms);
    while (delay_ms < 0);

    Hanoi *hanoi = HanoiCreate(ndiscos, ListSize(nomes_lista), nomes);

    setvbuf(stdout, NULL, _IOFBF, 4096);
    HanoiSolve(hanoi, delay_ms);

    HanoiDelete(&hanoi);

    getchar();

    return 0;
}
