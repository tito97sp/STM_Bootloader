/*
 * Bootloader.h
 *
 *  Created on: Jul 14, 2021
 *      Author: asanchez
 */

#ifndef BL_MEM_LOOP_H_
#define BL_MEM_LOOP_H_

#include <image_hdr.h>
#include "string.h"
#include "fatfs.h"

#include <stdio.h>
#include <string.h>
#include <stdarg.h>



typedef void (*ptrF)(void);

//some variables for FatFs
FATFS FatFs; 	//Fatfs handle
FIL fil; 		//File handle
FRESULT fres; //Result after operations




void bl_fatsd(unsigned timeout);

BYTE image_check(const char *image_path, image_hdr_t *image_hdr_ptr);


int image_validate(const image_hdr_t *hdr);



#endif /* BL_MEM_LOOP_H_ */
