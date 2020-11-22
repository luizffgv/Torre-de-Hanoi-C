#include <stdio.h>
#include <stdlib.h>

// TEMP
#include "crosssleep.h"

#include "hanoimonks.h"
#include "list.h"
#include "queue.h"

struct HanoiMonks_
{
    Queue *monks;
    List *scores;
};

HanoiMonks *HanoiMonksNew(size_t nmonks, char **names)
{
    HanoiMonks *monks = malloc(sizeof(*monks));
    monks->monks      = QueueNew();
    monks->scores     = ListNew();

    for (size_t monk_i = 0; monk_i < nmonks; ++monk_i)
    {
        HanoiMonk *monk = HanoiMonkNew(names[monk_i]);
        QueueEnqueue(monks->monks, monk);

        long long *score = calloc(1, sizeof(*score));
        ListAppend(&monks->scores, score);
    }

    return monks;
}

void HanoiMonksDelete(HanoiMonks **monks)
{
    QueueDelete((*monks)->monks, (void (*)(void *))HanoiMonkDelete);
    ListDestroy(&(*monks)->scores, NULL);

    free(*monks);
    *monks = NULL;
}

void HanoiMonksPeek(HanoiMonks *monks, HanoiMonk *monk, long long *score)
{
    if (monk)
        HanoiMonkCpy(monk, QueuePeek(monks->monks));
    if (score)
        *score = *(long long *)ListGet(monks->scores, 0);
}

void HanoiMonksScoreAdd(HanoiMonks *monks, int score)
{
    long long *node = ListGet(monks->scores, 0);

    *node += score;

    // Avançar a lista
    ListAppend(&monks->scores, node);
    ListRemove(&monks->scores, 0, NULL);

    // Avançar a fila
    QueueEnqueue(monks->monks, QueueDequeue(monks->monks));
}

void HanoiMonksPrint(HanoiMonks *monks)
{
    Queue *monks_old = monks->monks;
    List **scores    = &monks->scores;
    Queue *monks_new = QueueNew();

    while (!QueueIsEmpty(monks_old))
    {
        HanoiMonk *monk = QueueDequeue(monks_old);
        char name[HanoiMonkNameSz(monk)];
        HanoiMonkNameCpy(monk, name);

        long long *score = ListGet(*scores, 0);
        ListAppend(scores, score);
        ListRemove(scores, 0, NULL);

        printf("%-32s | %lld pts\n", name, *score);
    }

    fflush(stdout);
}
