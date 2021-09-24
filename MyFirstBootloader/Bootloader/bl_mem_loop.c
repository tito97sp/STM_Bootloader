#include <bl_mem_loop.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h> //for va_list var arg functions
#include <crc32.h>
const char image_name[] = "firmware_v1.bin";

void bl_fatsd(unsigned timeout)
{
	//bl_type = NONE; // The type of the bootloader, whether loading from USB or USART, will be determined by on what port the bootloader recevies its first valid command.
	//volatile uint32_t  bl_state = 0; // Must see correct command sequence to erase and reboot (commit first word)
	uint32_t  address = 0; 	//board_info.fw_size; /* force erase before upload will work */
	uint32_t  first_word = 0xffffffff;

	/* (re)start the timer system */
	//	arch_systic_init();

	/* if we are working with a timeout, start it running */
	//	if (timeout) {
	//		timer[TIMER_BL_WAIT] = timeout;
	//	}

	/* make the LED blink while we are idle */
	// led_set(LED_BLINK);
	static union {
		uint8_t   c[256];
		uint32_t  w[64];
	} flash_buffer;

	// Wait for a command byte
	// led_off(LED_ACTIVITY);

	// open firmware binary from sd card.
	//Open the file system

	HAL_Delay(1000);

	fres = f_mount(&FatFs, "", 1); //1=mount now
	if (fres != FR_OK)
	{
		printf("f_mount error \r\n");
		return;
	}


//	DWORD free_clusters, free_sectors, total_sectors;
//	FATFS* getFreeFs;
//
//	fres = f_getfree("", &free_clusters, &getFreeFs);
//	if (fres != FR_OK) {
//		//sprintf("f_getfree error (%i)\r\n", fres);
//		while(1);
//	}

//	//Formula comes from ChaN's documentation
//	total_sectors = (getFreeFs->n_fatent - 2) * getFreeFs->csize;
//	free_sectors = free_clusters * getFreeFs->csize;

	//sprintf("SD card stats:\r\n%10lu KiB total drive space.\r\n%10lu KiB available.\r\n", total_sectors / 2, free_sectors / 2);

	///Now let's try to open file "test.txt"
//	fres = f_open(&fil, "firmware_app.bin", FA_READ);
//	if (fres != FR_OK) {
//		//sprintf("f_open error (%i)\r\n");
//		while(1);
//	 }
	//sprintf("I was able to open 'test.txt' for reading!\r\n");

	//Read 30 bytes from "test.txt" on the SD card
	//uint32_t readBuf[512/4];

	//We can either use f_read OR f_gets to get data out of files
	//f_gets is a wrapper on f_read that does some string formatting for us
//	TCHAR* rres = f_gets((TCHAR*)readBuf, sizeof(readBuf), &fil);
//	if(rres != 0) {
//		//sprintf("Read string from 'test.txt' contents: %s\r\n", readBuf);
//	} else {
//		//sprintf("f_gets error (%i)\r\n", fres);
//	}

	//Be a tidy kiwi - don't forget to close your file!
//	f_close(&fil);



	//Locate and check for loadable firmware. (iterate over images to find the latest and make checks).
	const image_hdr_t *image_hdr;

	//iterate over files.
	IMAGE_STATUS ires;
	ires = image_check(image_name, image_hdr);
	if(ires != IMA_OK)
	{
		return;
	}

	printf("New valid image found in SD. Uploading firmware...\r\n");




	printf("Uploading image");


	//led_on(LED_ACTIVITY);

	// erase and prepare for programming

	// check if available to erase.
	//if ((bl_state & STATE_ALLOWS_ERASE) != STATE_ALLOWS_ERASE) {
		//goto cmd_bad;
	//}

	// unblock and erase all sectors
	//	arch_flash_unlock();

	//for (int i = 0; flash_func_sector_size(i) != 0; i++)
	//{
		//flash_func_erase_sector(i);
	//}

	// verify the erase
//	for (address = 0; address < board_info.fw_size; address += 4)
//	{
//		//if (flash_func_read_word(address) != 0xffffffff) {
//		//	goto cmd_fail;
//		//}
//	}

	address = 0;
	uint8_t EndOfFIle = 0;
	while(!EndOfFIle)
	{
		uint8_t readBytes = 0;

		// read maximum number of bytes from file.
		FRESULT rres = f_read(&fil, &flash_buffer.c[0], sizeof(flash_buffer.c)/sizeof(flash_buffer.c[0]), (UINT*)&readBytes);
		if(rres != FR_OK) {
			printf("Read string from 'test.txt' contents:\r\n");
		} else {
			printf("f_gets error (%i)\r\n", fres);
		}

		// check if end of file reached.
		if(sizeof(flash_buffer.c)/sizeof(flash_buffer.c[0]) > readBytes)
		{
			//EOF = 1;
		}

		if (readBytes < 0)
		{
			//goto cmd_bad;
		}

		// sanity-check arguments
		if (readBytes % 4)
		{
			//goto cmd_bad;
		}

	//		if ((address + readBytes) > board_info.fw_size)
	//		{
	//			//goto cmd_bad;
	//		}

		if (readBytes > sizeof(flash_buffer.c)/sizeof(flash_buffer.c[0]))
		{
			//goto cmd_bad;
		}

		// sanity-checks
		for(uint8_t i = 0; i < readBytes; i++)
		{
			//if (flash_buffer.c[i] < 0) {
			//	goto cmd_bad;
			//}
		}

		if (address == 0)
		{
			// save the first word and don't program it until everything else is done.
			//first_word = flash_buffer.c[0];
			// replace first word with bits we can overwrite later
			//flash_buffer.c[0] = 0xffffffff;
		}

		readBytes /= 4;

		for (uint8_t i = 0; i < readBytes; i++)
		{
			// program the word
			//flash_func_write_word(address, flash_buffer.c[i*4]);
			// do immediate read-back verify
			//if (flash_func_read_word(address) != flash_buffer.c[i*4]) {
			//	goto cmd_fail;
			//}

			address += 4;
		}
	}

		// fetch CRC of the entire flash area
		if(0)
		{
			// compute CRC of the programmed area
			//uint32_t sum = 0;

//			for (unsigned p = 0; p < board_info.fw_size; p += 4)
//			{
//				//uint32_t bytes;
//				if ((p == 0) && (first_word != 0xffffffff)) {
//				//bytes = first_word;
//				} else {
//				//bytes = flash_func_read_word(p);
//				}
//				//sum = crc32((uint8_t *)&bytes, sizeof(bytes), sum);
//			}

			//cout_word(sum);
		}


	//Close file
	f_close(&fil);

	//Unmount the drive
	f_mount(NULL, "", 0);

	// finalise programming and boot the system

	//	if (first_word != 0xffffffff && (bl_state & STATE_ALLOWS_REBOOT) != STATE_ALLOWS_REBOOT) {
	//		goto cmd_bad;
	//	}

	// program the deferred first word
	if (first_word != 0xffffffff) {
		//flash_func_write_word(0, first_word);
		//if (flash_func_read_word(0) != first_word) {
		//	goto cmd_fail;
		//}

		// revert in case the flash was bad...
		first_word = 0xffffffff;
	}


	// start image
	image_start(image_hdr);


//cmd_bad:
		// send an 'invalid' response but don't kill the timeout - could be garbage
		//invalid_response();
		//continue;

//cmd_fail:
		// send a 'command failed' response but don't kill the timeout - could be garbage
		//failure_response();
		//continue;

}



IMAGE_STATUS image_check(const char *image_path,  image_hdr_t *image_hdr_ptr)
{
	//read image_hdr_t
	uint8_t readBytes = 0;
	uint8_t ima_hdr_buff[sizeof(image_hdr_t)];

	IMAGE_STATUS istat = IMA_OK;
	FRESULT fres;

	//open the file.
	fres = f_open(&fil, "firmware_app.bin", FA_READ);
	if (fres != FR_OK) {
		istat =  IMA_NOT_FOUND;
	}

	// read maximum number of bytes from file.
	fres = f_read(&fil, &ima_hdr_buff, sizeof(image_hdr_t), (UINT*)&readBytes);
	if(fres != FR_OK) {
		istat = IMA_ERROR;
	}

	// EOF reached?
	if(sizeof(image_hdr_t) > readBytes)
	{
		istat = IMA_ERROR;
	}

	// cast image_hdr
	const image_hdr_t *hdr = NULL;
	hdr = (const image_hdr_t *)&ima_hdr_buff[0];

	// Check header.
	if(istat == IMA_OK){
		// perform image checks (crc, minimal version, data_size, vector_addr)
		if (hdr && hdr->image_magic == IMAGE_MAGIC
				&& hdr->crc != 0
				&& hdr->data_size != 0
				&& hdr->vector_addr != 0)
		{
			*image_hdr_ptr = *hdr;
			istat = IMA_OK;
		}
		else
		{
			image_hdr_ptr = NULL;
			istat = IMA_INVALID;
		}
	}

	if(istat == IMA_OK)
	{
		// move to vect_addr
		uint8_t byte[512-52];
		//uint32_t unused_hdr_length = image_hdr_ptr->vector_addr - sizeof(image_hdr_t);
		//for (uint32_t p = 0; p < unused_hdr_length+1; p++)
		//{
			//uint8_t byte;
			fres = f_read(&fil, &byte, sizeof(byte), (UINT*)&readBytes);
		//}

		// compute CRC of the programmed area
		uint32_t sum = ~0U;
		uint32_t app_length = image_hdr_ptr->data_size - image_hdr_ptr->vector_addr;
		for (uint32_t p = 0; p < app_length; p += 4)
		{
			// get data from external
			uint32_t bytes;
			fres = f_read(&fil, &bytes, sizeof(bytes), (UINT*)&readBytes);
			if(fres != FR_OK) {
				istat = IMA_ERROR;
			}

			sum = crc32((uint8_t *)&bytes, sizeof(bytes), sum);
		}
		sum = sum ^ ~0U;

		if(hdr->crc != sum)
		{
		   printf("Error. Image binary corruption");
		   return 0;
		}
	}

	// close file
	f_close(&fil);

	return istat;
}

int image_validate(const image_hdr_t *hdr) {
    // compute crc and compare with header to validate image.

//	void *addr = (slot == IMAGE_SLOT_1 ? &__slot1rom_start__ : &__slot2rom_start__);
//    addr += sizeof(image_hdr_t);
//    uint32_t len = hdr->data_size;
//    uint32_t a = crc32(addr, len);
//    uint32_t b = hdr->crc;
//    if (a == b) {
//        return 0;
//    } else {
//        printf("CRC Mismatch: %lx vs %lx\n", a, b);
//        return -1;
//    }
	return 0;
}



