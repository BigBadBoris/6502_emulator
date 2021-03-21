#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include "cpu.h"


/*
 * Addressing Modes
 */


/* Immediate: a literal 8-bit value */
uint16_t addr_immediate(Cpu * cpu){
	return cpu->pc++;
}


/* Absolute: a 16-bit address */
uint16_t addr_absolute(Cpu * cpu){
	// low byte
	uint16_t addr = cpu->mem_read(cpu->pc++);
	// high byte
	addr |= ((uint16_t)cpu->mem_read(cpu->pc++) << 8);
	return addr;
}

/* Zero Page: an address within the first 256 memory locations
   ($0000 - $00FF) : save a byte
 */
uint16_t addr_zero_page(Cpu * cpu){
	return (uint16_t) cpu->mem_read(cpu->pc++);
}

/* Implied: instruction is only one byte, argument is implied */
uint16_t addr_implied(Cpu * cpu){
	(void) cpu; 		/* NO-OP */
	return 0;
}

/* Indirect absolute addressing: dereferences memory location at 
   specified address and uses the value contained at that address and 
   address + 1  as new address, only used by JMP*/
uint16_t addr_indirect_absolute(Cpu * cpu){
	// pointer low byte
	uint16_t addr = cpu->mem_read(cpu->pc++);
	// pointer high byte
	addr |= ((uint16_t) cpu->mem_read(cpu->pc++) << 8);

	// dereference low byte
	uint16_t ret = cpu->mem_read(addr);
	// dereference high byte
	ret |= ((uint16_t) cpu->mem_read(addr + 1)) << 8;
	return ret;
}


/* Absolute Indexed Addressing: a 16-bit address offset by X
 * register */
uint16_t addr_absolute_indexed_x(Cpu * cpu){
	return addr_absolute(cpu) + cpu->x_reg;
}


/* Absolute Indexed Addressing: a 16-bit address offset by Y
 * register */
uint16_t addr_absolute_indexed_y(Cpu * cpu){
	return addr_absolute(cpu) + cpu->y_reg;
}


/* Zero paged indexed: an 8-bit address in first page offset by X
 * register */
uint16_t addr_zero_page_indexed_x(Cpu * cpu){
	return (addr_zero_page(cpu) + cpu->x_reg) & LOW_BYTE_MASK;
}


/* Zero paged indexed: an 8-bit address in first page offset by Y
 * register */
uint16_t addr_zero_page_indexed_y(Cpu * cpu){
	return (addr_zero_page(cpu) + cpu->y_reg) & LOW_BYTE_MASK;
}


/* Indexed indirect: add X offset to 8-bit pointer, then dereference
usually used for indexing into jump table stored in zero page   */

uint16_t addr_indexed_indirect_x(Cpu * cpu){
	uint16_t ptr = cpu->mem_read(cpu->pc++) + cpu->x_reg;
	// zero page wrap-around
	ptr &= LOW_BYTE_MASK;

	// read low byte
	uint16_t addr = cpu->mem_read(ptr);

	// increment pointer
	ptr++;

	// edge case where ptr == 255, we want to wrap around to stay
	// on zero page (I think?)
	ptr &= LOW_BYTE_MASK;

	// read high byte
	addr |= ((uint16_t)cpu->mem_read(ptr)) << 8;
	return addr;
}


/* Indexed indirect: add Y offset to 8-bit pointer, then dereference
usually used for indexing into jump table stored in zero page   */
uint16_t addr_indexed_indirect_y(Cpu * cpu){
	uint16_t ptr = cpu->mem_read(cpu->pc++) + cpu->y_reg;
	// zero page wrap-around
	ptr &= LOW_BYTE_MASK;

	// read low byte
	uint16_t addr = cpu->mem_read(ptr);

	// increment pointer
	ptr++;

	// edge case where ptr == 255, we want to wrap around to stay
	// on zero page (I think?)
	ptr &= LOW_BYTE_MASK;

	// read high byte
	addr |= ((uint16_t)cpu->mem_read(ptr)) << 8;
	
	return addr;
}


/* Find the 16-bit address contained in specified zero-page
 * location. Add to that new address the X offset */
uint16_t addr_indirect_indexed_x(Cpu * cpu){
	uint16_t addr = cpu->mem_read(cpu->pc++);

	// read low byte
	uint16_t ptr = cpu->mem_read(addr);
	addr++;
	addr &= LOW_BYTE_MASK;
	// read high byte
	ptr |= ((uint16_t) cpu->mem_read(addr)) << 8;
	ptr += cpu->x_reg;
	return ptr;
}

/* Find the 16-bit address contained in specified zero-page
 * location. Add to that new address the X offset */
uint16_t addr_indirect_indexed_y(Cpu * cpu){
	uint16_t addr = cpu->mem_read(cpu->pc++);

	// read low byte
	uint16_t ptr = cpu->mem_read(addr);
	addr++;
	addr &= LOW_BYTE_MASK;
	// read high byte
	ptr |= ((uint16_t) cpu->mem_read(addr)) << 8;
	ptr += cpu->x_reg;
	return ptr;
}


/* Accumulator : the A register is the implied operand */
uint16_t addr_accumulator(Cpu * cpu){
	return (uint16_t) cpu->acc;
}
