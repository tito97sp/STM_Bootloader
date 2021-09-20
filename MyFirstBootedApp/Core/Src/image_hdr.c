#include "image_hdr.h"


image_hdr_t image_hdr __attribute__((section(".image_hdr"))) =
{
		.image_magic = IMAGE_MAGIC,
		.image_hdr_version = IMAGE_HDR_VERSION,
		.image_type = IMAGE_TYPE_APP,
		.version_major = 1,
		.version_minor = 0,
		.version_path = 1,
		.compilation_date = COMPILATION_DATE,
		.compilation_time = COMPILATION_TIME,
		.vector_addr = 0x00000200UL,	//(uint32_t)&vector_table,
		.git_sha = GIT_SHA,
		.crc = 0,
		.data_size = 0,
		.image_hdr_size = sizeof(image_hdr_t)
};
