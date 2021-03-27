#include <stdint.h>
#include <stdbool.h>

#include "cpu.h"


/*
 * Load/Store Operations
 */


/* LoaD Accumulator */
void op_lda(Cpu * cpu, uint16_t arg){
	// load accumulator value
	cpu->acc = arg & LOW_BYTE_MASK;
	// set zero bit
	cpu_set_status_bit(cpu, STAT_ZERO, !cpu->acc);
	// set negative bit
	cpu_set_status_bit(cpu, STAT_NEG, cpu->acc & NEGATIVE_BIT);
}

/* LoaD X register */
void op_ldx(Cpu * cpu, uint16_t arg){
	// load x register value
	cpu->x_reg = arg & LOW_BYTE_MASK;
	// set zero bit
	cpu_set_status_bit(cpu, STAT_ZERO, !cpu->x_reg);
	// set negative bit
	cpu_set_status_bit(cpu, STAT_NEG, cpu->x_reg & NEGATIVE_BIT);
}

/* Load Y register */
void op_ldy(Cpu * cpu, uint16_t arg){
	// load x register value
	cpu->y_reg = arg & LOW_BYTE_MASK;
	// set zero bit
	cpu_set_status_bit(cpu, STAT_ZERO, !cpu->y_reg);
	// set negative bit
	cpu_set_status_bit(cpu, STAT_NEG, cpu->y_reg & NEGATIVE_BIT);
}

/* STore Accumulator  */
void op_sta(Cpu * cpu, uint16_t arg){
	cpu->mem_write(arg, cpu->acc);
}

/* STore X */
void op_stx(Cpu * cpu, uint16_t arg){
	cpu->mem_write(arg, cpu->x_reg);
}

/* STore X */
void op_sty(Cpu * cpu, uint16_t arg){
	cpu->mem_write(arg, cpu->y_reg);
}


/* 
 * Transfer Instructions
 */

/* Transfer the value from A to X */
void op_tax(Cpu * cpu, uint16_t arg){
	(void) arg; // not used
	// transfer acc to x
	cpu->x_reg = cpu->acc;
	// set zero bit
	cpu_set_status_bit(cpu, STAT_ZERO, !cpu->x_reg);
	// set negative bit
	cpu_set_status_bit(cpu, STAT_NEG, cpu->x_reg & NEGATIVE_BIT);
}

/* Transfer the value from A to Y */
void op_tay(Cpu * cpu, uint16_t arg){
	(void) arg; // not used
	// transfer acc to y
	cpu->y_reg = cpu->acc;
	// set zero bit
	cpu_set_status_bit(cpu, STAT_ZERO, !cpu->y_reg);
	// set negative bit
	cpu_set_status_bit(cpu, STAT_NEG, cpu->y_reg & NEGATIVE_BIT);
}

/* Transfer the value from X to A */
void op_txa(Cpu * cpu, uint16_t arg){
	(void) arg; // not used
	cpu->acc = cpu->x_reg;
	// set zero bit
	cpu_set_status_bit(cpu, STAT_ZERO, !cpu->acc);
	// set negative bit
	cpu_set_status_bit(cpu, STAT_NEG, cpu->acc & NEGATIVE_BIT);
}

/* Transfer the value from Y to A */
void op_tya(Cpu * cpu, uint16_t arg){
	(void) arg; // not used
	cpu->acc = cpu->y_reg;
	// set zero bit
	cpu_set_status_bit(cpu, STAT_ZERO, !cpu->acc);
	// set negative bit
	cpu_set_status_bit(cpu, STAT_NEG, cpu->acc & NEGATIVE_BIT);	
}

/*
 * Arithmetic OPERATIONS
 */

/* Add with carry */
void op_adc(Cpu * cpu, uint16_t arg){
	// read value from memory
	uint8_t val = cpu->mem_read(arg);
	// do addition and set it to temporary variable
	uint16_t temp = cpu->acc + val + (cpu_is_status_bit_set(cpu, STAT_CARRY) ? 1 : 0);
	// set zero status bit if addition resulted in a 0
	cpu_set_status_bit(cpu, STAT_ZERO, !(temp & LOW_BYTE_MASK));
	if (cpu_is_status_bit_set(cpu, STAT_DECIMAL)){ // decimal addition
		// TODO implement decimal mode addition
	} else { // binary addition
		// set negative status bit
		cpu_set_status_bit(cpu, STAT_NEG, (temp & NEGATIVE_BIT));
		// set carry bit
		cpu_set_status_bit(cpu, STAT_CARRY, (temp > MAX_UINT8_T));
		// checking for overflow:
		//it has occurred if the result is the opposite sign of the operands
		// AND the operands are of same sign 
		bool operands_same_sign = !((cpu->acc ^ val) & NEGATIVE_BIT);
		bool result_and_acc_opposite_sign = (cpu->acc ^ temp) & NEGATIVE_BIT;
		bool overflow = operands_same_sign && result_and_acc_opposite_sign;
		// set overflow bit
		cpu_set_status_bit(cpu, STAT_OVERFLOW, overflow);
	}
	// set accumulator value
	cpu->acc = (temp & LOW_BYTE_MASK);
}

void op_sbc(Cpu * cpu, uint16_t arg){
	// TODO FIXME
	
	// read value from memory
	const int8_t val = (int8_t) cpu->mem_read(arg);
	const bool carry_set = cpu_is_status_bit_set(cpu, STAT_CARRY);
	const bool decimal_set = cpu_is_status_bit_set(cpu, STAT_DECIMAL);
	// do substraction, which is A - VAL - ~Carry
	const int16_t temp = ((int8_t)cpu->acc) - val - ((carry_set) ? 0 : 1);
	// set zero status bit if subtraction resulted in a zero
	cpu_set_status_bit(cpu, STAT_ZERO, !(temp & LOW_BYTE_MASK));
	if (decimal_set){
		// TODO
	} else {
		// set negative status bit
		cpu_set_status_bit(cpu, STAT_NEG, (temp & NEGATIVE_BIT));
		// check for underflow
		
	}
}


/*
 * Increment/Decrement Instructions
 */

/* Increment memory by one */
void op_inc(Cpu * cpu, uint16_t address){
	uint8_t val = cpu->mem_read(address);
	val++;
	// set zero status bit
	cpu_set_status_bit(cpu, STAT_ZERO, val == 0);
	// set negative bit
	cpu_set_status_bit(cpu, STAT_ZERO, val & NEGATIVE_BIT);
	cpu->mem_write(address, val);
}

/* Increment X register by one */
void op_inx(Cpu * cpu, uint16_t arg){
	(void) arg;
	const uint8_t val = ++(cpu->x_reg);
	// set zero status bit
	cpu_set_status_bit(cpu, STAT_ZERO, val == 0);
	// set negative bit
	cpu_set_status_bit(cpu, STAT_ZERO, val & NEGATIVE_BIT);
}

/* Increment Y register by one */
void op_iny(Cpu * cpu, uint16_t arg){
	(void) arg;
	const uint8_t val = ++(cpu->y_reg);
	// set zero status bit
	cpu_set_status_bit(cpu, STAT_ZERO, val == 0);
	// set negative bit
	cpu_set_status_bit(cpu, STAT_ZERO, val & NEGATIVE_BIT);
}

/* Decrement memory by one */
void op_dec(Cpu * cpu, uint16_t address){
	uint8_t val = cpu->mem_read(address);
	val--;
	// set zero status bit
	cpu_set_status_bit(cpu, STAT_ZERO, val == 0);
	// set negative bit
	cpu_set_status_bit(cpu, STAT_ZERO, val & NEGATIVE_BIT);
	// write value back to memory
	cpu->mem_write(address, val);
}

/* Decrement X register by one */
void op_dex(Cpu * cpu, uint16_t arg){
	(void) arg;
	const uint8_t val = --(cpu->x_reg);
	// set zero status bit
	cpu_set_status_bit(cpu, STAT_ZERO, val == 0);
	// set negative bit
	cpu_set_status_bit(cpu, STAT_ZERO, val & NEGATIVE_BIT);
}

/* Decrement Y register by one */
void op_dey(Cpu * cpu, uint16_t arg){
	(void) arg;
	const uint8_t val = --(cpu->y_reg);
	// set zero status bit
	cpu_set_status_bit(cpu, STAT_ZERO, val == 0);
	// set negative bit
	cpu_set_status_bit(cpu, STAT_ZERO, val & NEGATIVE_BIT);
}

/*
 * LOGICAL OPERATIONS
 */

/* AND memory with accumulator */
void op_and(Cpu * cpu, uint16_t arg){
	uint8_t val = cpu->mem_read(arg);
	cpu->acc &= val;
	val = cpu->acc;
	// set zero status bit
	cpu_set_status_bit(cpu, STAT_ZERO, val == 0);
	// set negative bit
	cpu_set_status_bit(cpu, STAT_ZERO, val & NEGATIVE_BIT);
}

/* OR memory with accumulator */
void op_ora(Cpu * cpu, uint16_t arg){
	uint8_t val = cpu->mem_read(arg);
	cpu->acc |= val;
	val = cpu->acc;
	// set zero status bit
	cpu_set_status_bit(cpu, STAT_ZERO, val == 0);
	// set negative bit
	cpu_set_status_bit(cpu, STAT_ZERO, val & NEGATIVE_BIT);
}

/* XOR memory with accumulator */
void op_eor(Cpu * cpu, uint16_t arg){
	uint8_t val = cpu->mem_read(arg);
	cpu->acc ^= val;
	val = cpu->acc;
	// set zero status bit
	cpu_set_status_bit(cpu, STAT_ZERO, val == 0);
	// set negative bit
	cpu_set_status_bit(cpu, STAT_ZERO, val & NEGATIVE_BIT);
}



/*
 *  STATUS OPERATIONS
 */

/* Clear carry status flag */
void op_clc(Cpu * cpu, uint16_t arg){
	(void) arg;
	cpu_set_status_bit(cpu, STAT_CARRY, false);
}

/* Clear decimal status flag */
void op_cld(Cpu * cpu, uint16_t arg){
	(void) arg;
	cpu_set_status_bit(cpu, STAT_DECIMAL, false);
}

/* Clear interrupt disable */
void op_cli(Cpu * cpu, uint16_t arg){
	(void) arg;
	cpu_set_status_bit(cpu, STAT_IRQ_DISABLE, false);
}

/* Clear overflow */
void op_clv(Cpu * cpu, uint16_t arg){
	(void) arg;
	cpu_set_status_bit(cpu, STAT_OVERFLOW, false);
}
