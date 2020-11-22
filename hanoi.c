#include <stdio.h>
#include <stdlib.h>

#include "crosssleep.h"
#include "hanoi.h"
#include "hanoimonks.h"
#include "list.h"

struct Hanoi_
{
    HanoiMonks *monks;
    Stack *from;
    Stack *aux;
    Stack *to;
    unsigned ndisks;
    unsigned long long moves;
};

void MoveDisk_(Hanoi *hanoi, Stack *from, Stack *to);
void HanoiPrint(size_t ndisks, Stack *from, Stack *aux, Stack *to);
void TerminalClear(void);

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

    TerminalClear();
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
    if (from == hanoi->to)
        HanoiMonksScoreAdd(hanoi->monks, -3);

    HanoiMonk *monk = HanoiMonkNew("Temp_name");

    long long score;
    HanoiMonksPeek(hanoi->monks, monk, &score);

    char monk_name[HanoiMonkNameSz(monk)];
    HanoiMonkNameCpy(monk, monk_name);

    HanoiMonkDelete(monk);

    char from_ch = from == hanoi->from ? 'A' : from == hanoi->to ? 'C' : 'B';
    char to_ch   = to == hanoi->from ? 'A' : to == hanoi->to ? 'C' : 'B';

    TerminalClear();
    printf("Monge %-16.16s - %5lld pts: Movendo %c para %c\n"
           "Movimentos: %llu\n ",
           monk_name, score, from_ch, to_ch, hanoi->moves);

    StackPush(to, StackPop(from));

    HanoiPrint(hanoi->ndisks, hanoi->from, hanoi->aux, hanoi->to);
    fflush(stdout);
}

void HanoiPrint(size_t ndisks, Stack *from, Stack *aux, Stack *to)
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

void TerminalClear(void)
{
#ifdef __unix__
    system("clear");
#elif defined _WIN32
    system("cls");
#endif  // defined __unix__
}
