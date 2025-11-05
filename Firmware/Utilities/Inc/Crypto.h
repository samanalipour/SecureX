/*
 * Crypto.h
 *
 *  Created on: Oct 25, 2024
 *      Author: saman
 */

#ifndef INC_CRYPTO_H_
#define INC_CRYPTO_H_
#include "main.h"
void sha256(uint8_t *data,uint8_t *result,uint8_t DataSize);
void AESCBC(uint8_t *Data, uint8_t DataSize, uint8_t *Key, uint8_t KeySize, uint8_t *IVF,uint8_t IVFSize, uint8_t *result);
void DecryptAES(uint8_t *Data, uint8_t DataSize, uint8_t *Key, uint8_t KeySize, uint8_t *IVF,uint8_t IVFSize, uint8_t *result);


#endif /* INC_CRYPTO_H_ */
