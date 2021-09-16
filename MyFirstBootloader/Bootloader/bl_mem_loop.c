#include <bl_mem_loop.h>

const char image_name[] = "firmware_v1.bin";

void bootloader_sd(unsigned timeout)
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
	fres = f_mount(&FatFs, "", 1); //1=mount now
	if (fres != FR_OK)
	{
		printf("f_mount error \r\n");
		return;
	}


	//Locate and check for loadable firmware. (iterate over images to find the latest and make checks).
	const image_hdr_t *image_hdr;
	image_hdr = image_get_header(image_name);
	uint8_t err = image_validate(image_hdr);
	if(err != 0)
	{
		return;
	}
	printf("New valid image found in SD. Uploading firmware...\r\n");


	//Open new firmware to load.
	fres = f_open(&fil, image_name, FA_READ);
	if (fres != FR_OK)
	{
		printf("f_open error \r\n");
		return;
	}
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

const image_hdr_t *image_get_header(const char *image_path)
{
	//open the file.

	//read image_hdr_t
	uint8_t readBytes = 0;
	uint8_t ima_hdr_buff[sizeof(image_hdr_t)];

	// read maximum number of bytes from file.
	FRESULT rres = f_read(&fil, &ima_hdr_buff, sizeof(image_hdr_t), (UINT*)&readBytes);
	if(rres != FR_OK) {
		printf("Error.");
	}

	// check if end of file reached.
	if(sizeof(image_hdr_t) > readBytes)
	{
		printf("Error.");
	}

	// cast
	const image_hdr_t *hdr = NULL;
	hdr = (const image_hdr_t *)&ima_hdr_buff[0];

	return hdr;

	if (hdr && hdr->image_magic == IMAGE_MAGIC) {
	        return hdr;
	    } else {
	        return NULL;
	    }
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



