/*
 * Menu.h
 *
 *  Created on: Oct 25, 2024
 *      Author: saman
 */

#ifndef INC_MENU_H_
#define INC_MENU_H_
#include "main.h"
extern uint8_t Brand_new;
extern uint8_t GlobalSalt[8];
extern RNG_HandleTypeDef hrng;
extern StateType state;
extern StateType MenuState;
extern bool DeviceState;
extern uint32_t Timer;
extern uint8_t password[12];
extern uint8_t user_num;
extern uint8_t LocalSalt[8];
extern uint8_t IV[16];
extern uint8_t MasterKey[16];
extern uint8_t WrongPassword;
extern uint8_t CurrentPassword[12];
extern uint8_t CurrentMasterKey[16];
extern uint8_t CurrentLocalSalt[8];
extern uint8_t CurrentUser;
extern uint8_t CurrentIV[16];
void Startup();
void MainMenu();
void TimeoutMenu();
void Enroll();
bool CheckPassword();
void LockDevice();
void EraseAlaram();
void EraseMem();
void ResetFactory();
void OledAlarm();
#endif /* INC_MENU_H_ */
