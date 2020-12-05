// github.com/luizffgv

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hanoi.h"
#include "list.h"

int main(void)
{
    List *nomes_lista = ListNew();

    //
    // * Ler e armazenar nomes em uma lista
    //
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

    //
    // * Converter lista de nomes em array de ponteiros
    //
    char *nomes[ListSize(nomes_lista)];
    for (size_t nome_i = 0; nome_i < ListSize(nomes_lista); ++nome_i)
        nomes[nome_i] = ListGet(nomes_lista, nome_i);

    //
    // * Ler informações adicionais
    //
    int ndiscos;
    fputs("Discos: ", stdout);
    do scanf("%d", &ndiscos);
    while (ndiscos <= 0);

    int delay_ms;
    fputs("Delay por jogada (ms): ", stdout);
    do scanf("%d%*c", &delay_ms);
    while (delay_ms < 0);

    //
    // * Criar e executar jogo
    //
    Hanoi *hanoi = HanoiCreate(ndiscos, ListSize(nomes_lista), nomes);

    // Para que o terminal não exiba quadros parciais
    setvbuf(stdout, NULL, _IOFBF, 8192);
    HanoiSolve(hanoi, delay_ms);
    // Desativando buffer de saída agora
    setvbuf(stdout, NULL, _IONBF, 0);

    HanoiDelete(&hanoi);

    fputs("ENTER para continuar...", stdout);
    getchar();

    return 0;
}
