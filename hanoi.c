/**
 * @file hanoi.c
 * @author Luiz Fernando F. G. Valle (github.com/luizffgv)
 * @brief Implementation of the module hanoi
 * @version 1.0
 * @date 2020-11-26
 *
 * @copyright Copyright (c) 2020.
 *            Licensed under the GPL-3.0 License.
 *            See LICENSE in the project root for license information
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "crosssleep.h"
#include "hanoi.h"
#include "hanoimonks.h"
#include "list.h"

/**
 * @brief Internal representation of Hanoi
 *
 */
struct Hanoi_
{
    HanoiMonks *monks;
    Stack *from;
    Stack *aux;
    Stack *to;
    unsigned ndisks;
    unsigned long long moves;
};

/**
 * @brief Internal function that moves a disk from from to to
 *
 * @param hanoi Pointer to a game of towers of hanoi
 * @param from  Pointer to the source stack
 * @param to    Pointer to the destination stack
 */
void MoveDisk_(Hanoi *hanoi, Stack *from, Stack *to);

/**
 * @brief Internal function that displays the towers of a game of hanoi
 *
 * @param ndisks Total of disks in the game
 * @param from   First tower
 * @param aux    Second tower
 * @param to     Third tower
 */
void HanoiPrint_(size_t ndisks, Stack *from, Stack *aux, Stack *to);

/**
 * @brief Internal cross-platform function that clears the terminal
 *
 */
void TerminalClear_(void);

Hanoi *HanoiCreate(unsigned ndisks, size_t nmonks, char **names)
{
    Hanoi *hanoi = malloc(sizeof(*hanoi));

    hanoi->ndisks = ndisks;
    hanoi->moves  = 0;

    hanoi->monks = HanoiMonksNew(nmonks, names);

    hanoi->from = StackNew();
    hanoi->aux  = StackNew();
    hanoi->to   = StackNew();

    for (unsigned disk_i = 0; disk_i < ndisks; ++disk_i)
    {
        size_t *node = malloc(sizeof(*node));
        *node        = ndisks - disk_i;
        StackPush(hanoi->from, node);
    }

    return hanoi;
}

void HanoiDelete(Hanoi **hanoi)
{
    HanoiMonksDelete(&(*hanoi)->monks);

    StackDelete((*hanoi)->from, free);
    StackDelete((*hanoi)->aux, free);
    StackDelete((*hanoi)->to, free);

    free(*hanoi);
    *hanoi = NULL;
}

void HanoiSolve_(size_t disks,
                 Stack *from,
                 Stack *aux,
                 Stack *to,
                 Hanoi *hanoi,
                 int delay_ms);

void HanoiSolve(Hanoi *hanoi, int delay_ms)
{
    HanoiSolve_(hanoi->ndisks, hanoi->from, hanoi->aux, hanoi->to, hanoi,
                delay_ms);

    TerminalClear_();
    HanoiMonksPrint(hanoi->monks);
    fflush(stdout);
}

void HanoiSolve_(size_t disks,
                 Stack *from,
                 Stack *aux,
                 Stack *to,
                 Hanoi *hanoi,
                 int delay_ms)
{
    if (disks == 1)
    {
        MoveDisk_(hanoi, from, to);
        CrossSleep(delay_ms);
    }
    else
    {
        HanoiSolve_(disks - 1, from, to, aux, hanoi, delay_ms);

        MoveDisk_(hanoi, from, to);
        CrossSleep(delay_ms);
        HanoiSolve_(disks - 1, aux, from, to, hanoi, delay_ms);
    }
}

void MoveDisk_(Hanoi *hanoi, Stack *from, Stack *to)
{
    ++hanoi->moves;

    if (to == hanoi->to)
        HanoiMonksScoreAdd(hanoi->monks, 3);
    else if (from == hanoi->to)
        HanoiMonksScoreAdd(hanoi->monks, -3);
    else
        HanoiMonksScoreAdd(hanoi->monks, 0);

    HanoiMonk *monk = HanoiMonkNew("Temp_name");

    long long score;
    HanoiMonksPeek(hanoi->monks, monk, &score);

    char monk_name[HanoiMonkNameSz(monk)];
    HanoiMonkNameCpy(monk, monk_name);

    HanoiMonkDelete(monk);

    char from_ch = from == hanoi->from ? 'A' : from == hanoi->to ? 'C' : 'B';
    char to_ch   = to == hanoi->from ? 'A' : to == hanoi->to ? 'C' : 'B';

    TerminalClear_();
    printf("Monge %-16.16s - %5lld pts: Movendo %c para %c\n"
           "Movimentos: %llu\n ",
           monk_name, score, from_ch, to_ch, hanoi->moves);

    StackPush(to, StackPop(from));

    HanoiPrint_(hanoi->ndisks, hanoi->from, hanoi->aux, hanoi->to);
    fflush(stdout);
}

void HanoiPrint_(size_t ndisks, Stack *from, Stack *aux, Stack *to)
{
    const size_t TABS_BETWEEN_STACKS = 3;

    size_t stacks[3];

    stacks[0] = StackSize(from);
    stacks[1] = StackSize(aux);
    stacks[2] = StackSize(to);

    for (size_t line = ndisks; line; --line)
    {
        for (size_t stack_i = 0; stack_i < 3; ++stack_i)
        {
#ifdef __unix__
            switch (stack_i)
            {
            case 0: fputs("\033[31m", stdout); break;
            case 1: fputs("\033[32m", stdout); break;
            case 2: fputs("\033[34m", stdout); break;
            }
#endif  // #ifdef __unix__
            if (line <= stacks[stack_i])
#ifdef __unix__
                fputs("█", stdout);
#else
                putchar('X');
#endif  // #ifdef __unix__
            else
                putchar(' ');
            for (size_t tab = 0; tab < TABS_BETWEEN_STACKS; ++tab)
                putchar('\t');
        }
        putchar('\n');
    }

#ifdef __unix__
    fputs("\033[0;0m", stdout);
#else  // #ifdef __unix__
    puts("Cores disponiveis apenas em UNIX.");
#endif  // #ifdef __unix__
}

void TerminalClear_(void)
{
#ifdef __unix__
    system("clear");
#elif defined _WIN32
    system("cls");
#endif  // defined __unix__
}
