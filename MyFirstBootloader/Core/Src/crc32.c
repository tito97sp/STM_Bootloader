/*
 * crc32.c
 *
 *  Created on: 9 sept. 2021
 *      Author: asanchez
 */

#include <crc32.h>

uint32_t crc32(const uint8_t *src, uint32_t len, uint32_t state)
{
	static uint32_t crctab[256];

	/* check whether we have generated the CRC table yet */
	/* this is much smaller than a static table */
	if (crctab[1] == 0) {
		for (unsigned i = 0; i < 256; i++)
		{
			uint32_t c = i;

			for (unsigned j = 0; j < 8; j++)
			{
				if (c & 1)
				{
					c = 0xedb88320U ^ (c >> 1);
				}
				else
				{
					c = c >> 1;
				}
			}

			crctab[i] = c;
		}
	}

	for (unsigned i = 0; i < len; i++) {
		state = crctab[(state ^ src[i]) & 0xff] ^ (state >> 8);
	}

	return state;
}



