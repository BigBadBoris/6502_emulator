#ifndef __MEMORY_H
#define __MEMORY_H

#include <stdint.h>

#include "util.h"


/*
 *  Memory Areas: 16 bits
 */
#define ZERO_PAGE_START 0x0000
#define ZERO_PAGE_END	0x00FF

/* Stack Grows backwards from 0x01FF to 0x0100 */
#define STACK_TOP	0x0100
#define STACK_BOTTOM	0x01FF



#endif  /* __MEMORY_H */
