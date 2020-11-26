/**
 * @file hanoimonk.h
 * @author Luiz Fernando F. G. Valle (github.com/luizffgv)
 * @brief Interface of the module hanoimonk
 * @version 1.0
 * @date 2020-11-26
 *
 * @copyright Copyright (c) 2020.
 *            Licensed under the GPL-3.0 License.
 *            See LICENSE in the project root for license information
 *
 */

#ifndef HANOIMONK_H
#define HANOIMONK_H

#include <stddef.h>

/**
 * @brief Stores the information about a monk
 * 
 */
typedef struct HanoiMonk_ HanoiMonk;

/**
 * @brief Creates a monk
 *
 * @param name Name of the monk
 * @return     Address of newly created monk
 */
HanoiMonk *HanoiMonkNew(char *name);

/**
 * @brief Deletes a monk
 *
 * @param monk Address of a monk
 */
void HanoiMonkDelete(HanoiMonk *monk);

/**
 * @brief Copies a monk
 *
 * @param dest Destination monk
 * @param src  Source monk
 */
void HanoiMonkCpy(HanoiMonk *dest, HanoiMonk *src);

/**
 * @brief Returns the size of the monk's name
 *
 * @param monk Address of a monk
 * @return Size of the monk's name, including terminator
 */
size_t HanoiMonkNameSz(HanoiMonk *monk);

/**
 * @brief Copies the name of a monk
 *
 * @param monk Address of a monk
 * @param dest Address of a char array
 */
void HanoiMonkNameCpy(HanoiMonk *monk, char *dest);

#endif  // #ifndef HANOIMONK_H
