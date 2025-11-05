/*
 * Timer.c
 *
 *  Created on: Oct 26, 2024
 *      Author: saman
 */
#include "Timer.h"
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(htim);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_TIM_PeriodElapsedCallback could be implemented in the user file
   */
  if(DeviceState){
    Timer++;
    if(Timer == TimeoutValue){
      DeviceState=false;
      TimerState=true;    //false is lock, true unlock
      state=Lock;
      Timer=0;
    }
  }else{
    Timer=0;
  }
}
