#ifndef UTIL_H_
#define UTIL_H_

/* Utility Macro that returns a mask with only the x'th bit set */
#define BIT(x) (1 << x)

/* The negative bit for a signed byte  */
#define NEGATIVE_BIT 0x80
/* Mask for lower byte of a 16-bit word */
#define LOW_BYTE_MASK 0x00FF
/* Maximum size of an unsigned byte */
#define MAX_UINT8_T 0xFF

/* Size Defines */
#define SZ_1K	0x00000400
#define SZ_2K	0x00000800
#define SZ_4K	0x00001000
#define SZ_8K	0x00002000
#define SZ_16K	0x00004000
#define SZ_32K	0x00008000
#define SZ_64K	0x00010000


#endif	/* UTIL_H_ */
