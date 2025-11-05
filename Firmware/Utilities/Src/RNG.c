/*
 * RNG.c
 *
 *  Created on: Oct 25, 2024
 *      Author: saman
 */

#include "RNG.h"
bool rngflag =0;
void Get_rng(RNG_HandleTypeDef *hrng, uint8_t *rng,uint8_t NumRNG){
  for(int i=0;i<NumRNG;i++){
    HAL_RNG_GenerateRandomNumber_IT(hrng);
    while(!rngflag);
    rngflag =0;
    uint32_t temp_rng = HAL_RNG_ReadLastRandomNumber(hrng);
    for(int j=0;j<4;j++){
      rng[j+i*4] = (uint8_t)(temp_rng >> (j*8));
    }
  }
}

void HAL_RNG_ReadyDataCallback(RNG_HandleTypeDef *hrng, uint32_t random32bit){
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hrng);
  UNUSED(random32bit);
  /* NOTE : This function should not be modified. When the callback is needed,
            function HAL_RNG_ReadyDataCallback must be implemented in the user file.
   */
  rngflag =1;
}
