/**
 * @file hanoimonks.h
 * @author github.com/luizffgv
 * @date 2020-11-22
 */
#ifndef HANOIMONKS_H
#define HANOIMONKS_H

#include <stddef.h>

#include "hanoimonk.h"

typedef struct HanoiMonks_ HanoiMonks;

/**
 * @brief Creates a group of monks
 *
 * @param nmonks Number of monks
 * @param names Names of the monks
 * @return Address of a newly created group
 */
HanoiMonks *HanoiMonksNew(size_t nmonks, char **names);

/**
 * @brief Deletes a group of monks
 *
 * @param monks Group to be deleted
 */
void HanoiMonksDelete(HanoiMonks **monks);

/**
 * @brief Peeks the name and score of the next monk
 *
 * @param monks Group of monks
 * @param monk  Destination monk
 * @param score Destination score
 */
void HanoiMonksPeek(HanoiMonks *monks, HanoiMonk *monk, long long *score);

/**
 * @brief Adds a score to a monk and cycles through the monks
 *
 * @param monks Group of monks
 * @param score Score to be added
 */
void HanoiMonksScoreAdd(HanoiMonks *monks, int score);

/**
 * @brief Prints the monks' names and their scores
 *
 * @param monks Group of monks
 */
void HanoiMonksPrint(HanoiMonks *monks);

#endif  // #ifndef HANOIMONKS_H
