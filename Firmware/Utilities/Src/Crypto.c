/*
 * Crypto.c
 *
 *  Created on: Oct 25, 2024
 *      Author: saman
 */

#include "Crypto.h"

void sha256(uint8_t *data,uint8_t *result,uint8_t DataSize){
  size_t computed_size;
    cmox_hash_compute(CMOX_SHA256_ALGO,                /* Use SHA256 algorithm */
                 data, DataSize,           /* Message to digest */
               result,                   /* Data buffer to receive digest data */
               CMOX_SHA256_SIZE,         /* Expected digest size */
               &computed_size);          /* Size of computed digest */
}

void AESCBC(uint8_t *Data, uint8_t DataSize, uint8_t *Key, uint8_t KeySize, uint8_t *IVF,uint8_t IVFSize, uint8_t *result){
  size_t computed_size;
  cmox_cipher_encrypt(CMOX_AES_CBC_ENC_ALGO,                      /* Use AES CBC algorithm */
                     Data, DataSize,            /* Plaintext to encrypt */
                     Key, KeySize,              /* AES key to use */
                     IVF, IVFSize,              /* Initialization vector */
                     result, &computed_size);   /* Data buffer to receive generated ciphertext */
}

void DecryptAES(uint8_t *Data, uint8_t DataSize, uint8_t *Key, uint8_t KeySize, uint8_t *IVF,uint8_t IVFSize, uint8_t *result){
  size_t computed_size;
  cmox_cipher_decrypt(CMOX_AES_CBC_DEC_ALGO,                 /* Use AES CBC algorithm */
                   Data, DataSize,             /* Ciphertext to decrypt */
                                 Key, KeySize,               /* AES key to use */
                   IVF, IVFSize,               /* Initialization vector */
                   result, &computed_size);    /* Data buffer to receive generated plaintext */
}
