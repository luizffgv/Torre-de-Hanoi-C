/**
 * @file hanoi.h
 * @author Luiz Fernando F. G. Valle (github.com/luizffgv)
 * @brief Interface of the module hanoi
 * @version 1.0
 * @date 2020-11-26
 * 
 * @copyright Copyright (c) 2020.
 *            Licensed under the GPL-3.0 License.
 *            See LICENSE in the project root for license information
 * 
 */

#ifndef HANOI_H
#define HANOI_H

#include "hanoimonks.h"
#include "queue.h"
#include "stack.h"

/**
 * @brief Stores information of a game of towers of hanoi
 * 
 */
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
