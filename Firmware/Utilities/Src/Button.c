/*
 * Button.c
 *
 *  Created on: Oct 25, 2024
 *      Author: saman
 */
#include"Button.h"

int checkButtons(){
  bool flag_bt1  = true;
  bool flag_bt2  = true;
  bool flag_both = true;
  while(1){
    if(!DeviceState && TimerState){state=Lock;break;}
    if(Read_UP() && Read_DOWN() && flag_both){
      flag_both = false;
    }else if(Read_UP() && flag_bt1){
      flag_bt1 = false;
    }else if(Read_DOWN() && flag_bt2){
      flag_bt2 = false;
    }else if(!Read_UP() && !Read_DOWN() && !flag_both){
      flag_both = true;
      return 2;
    }else if(!Read_UP() && !flag_bt1 && flag_both){
      flag_bt1  = true;
      return 0;
    }else if(!Read_DOWN() && !flag_bt2 && flag_both){
      flag_bt2  = true;
      return 1;
    }
  }
  return 3;//nothing
}

bool Read_UP(){
  HAL_Delay(5);
  return HAL_GPIO_ReadPin(UP_GPIO_Port, UP_Pin);
}

bool Read_DOWN(){
  HAL_Delay(5);
  return HAL_GPIO_ReadPin(DOWN_GPIO_Port, DOWN_Pin);
}

