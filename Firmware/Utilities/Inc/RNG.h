/*
 * RNG.h
 *
 *  Created on: Oct 25, 2024
 *      Author: saman
 */

#ifndef INC_RNG_H_
#define INC_RNG_H_

#include "main.h"
void Get_rng(RNG_HandleTypeDef *hrng, uint8_t *rng,uint8_t NumRNG);
void HAL_RNG_ReadyDataCallback(RNG_HandleTypeDef *hrng, uint32_t random32bit);

#endif /* INC_RNG_H_ */
