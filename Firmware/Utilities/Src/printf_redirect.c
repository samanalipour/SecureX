/*
 * printf_redirect.c
 *
 *  Created on: Oct 25, 2024
 *      Author: saman
 */

#include "printf_redirect.h"
int _write(int file, char *ptr, int len){
  (void)file;
  int DataIdx;

  for (DataIdx = 0; DataIdx < len; DataIdx++)
  {
    ITM_SendChar(*ptr++);
  }
  return len;
}


void printArray(const char *arrayName, uint8_t *array, size_t size) {
    DEBUG_PRINT("%s: ", arrayName);
    for (size_t i = 0; i < size; i++) {
      DEBUG_PRINT("0x%02X ", array[i]);
    }
    DEBUG_PRINT("\n");
}
