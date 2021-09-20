/*
 * crc32.h
 *
 *  Created on: 9 sept. 2021
 *      Author: asanchez
 */

#ifndef INC_CRC32_H_
#define INC_CRC32_H_


#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdbool.h>

uint32_t crc32(const uint8_t *src, uint8_t len, uint32_t state);


#endif /* INC_CRC32_H_ */
