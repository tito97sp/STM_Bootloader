#ifndef IMAGE_HDR_H
#define IMAGE_HDR_H

#include <stdint.h>


#define IMAGE_MAGIC 		0xcafe
#define IMAGE_HDR_VERSION 	_IMAGE_HDR_VERSION_
#define COMPILATION_DATE    __DATE__
#define COMPILATION_TIME    __TIME__
#define IMAGE_TYPE_APP 		1
#define GIT_SHA				"undef"

typedef struct __attribute__((packed)){
	uint16_t image_magic;
	uint16_t image_hdr_version;
	uint32_t crc;
	uint32_t data_size;
	uint8_t  image_type;
	uint8_t  version_major;
	uint8_t  version_minor;
	uint8_t  version_path;
	char	 compilation_date[11];
	char 	 compilation_time[8];
	uint32_t vector_addr;
	uint32_t reserved;
	char     git_sha[8];
	uint16_t image_hdr_size;
}image_hdr_t;

#endif
