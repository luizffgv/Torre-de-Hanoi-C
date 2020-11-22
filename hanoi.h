/**
 * @file hanoi.h
 * @author github.com/luizffgv
 * @date 2020-11-22
 */
#ifndef HANOI_H
#define HANOI_H

#include "hanoimonks.h"
#include "queue.h"
#include "stack.h"

typedef struct Hanoi_ Hanoi;

/**
 * @brief Returns a game of Tower of Hanoi
 *
 * @param ndisks The number of disks to be moved
 * @param nmonks The number of monks in the game
 * @param names  The names of the monks
 *
 * @return Hanoi*
 */
Hanoi *HanoiCreate(unsigned ndisks, size_t nmonks, char **names);

/**
 * @brief Deletes a game of Tower of Hanoi
 *
 * @param hanoi Tower to be deleted
 */
void HanoiDelete(Hanoi **hanoi);

/**
 * @brief Solves a game of hanoi and displays the movements
 *
 * @param hanoi    Address of a game
 * @param delay_ms Delay between moves
 */
void HanoiSolve(Hanoi *hanoi, int delay_ms);

#endif  // #ifndef HANOI_H
