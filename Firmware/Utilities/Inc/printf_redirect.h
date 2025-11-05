/*
 * printf_redirect.h
 *
 *  Created on: Oct 25, 2024
 *      Author: saman
 */

#ifndef INC_PRINTF_REDIRECT_H_
#define INC_PRINTF_REDIRECT_H_
#include "main.h"
int _write(int file, char *ptr, int len);
void printArray(const char *arrayName, uint8_t *array, size_t size);
#endif /* INC_PRINTF_REDIRECT_H_ */
