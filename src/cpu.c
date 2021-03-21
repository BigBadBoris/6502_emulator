#include <stdint.h>
#include <stdbool.h>

#include "cpu.h"


/* Add with carry */
void op_adc(Cpu * cpu, uint16_t arg){
	// read value from memory
	uint8_t val = cpu->mem_read(arg);
	// do addition and set it to temporary variable
	uint16_t temp = cpu->acc + val + (cpu_is_status_bit_set(cpu, STAT_CARRY) ? 1 : 0);
	// set zero status bit if addition resulted in a 0
	cpu_set_status_bit(cpu, STAT_ZERO, !(temp & LOW_BYTE_MASK));
	if (cpu_is_status_bit_set(cpu, STAT_DECIMAL)){ // decimal addition
		// TODO
	} else { // binary addition
		// set negative status bit
		cpu_set_status_bit(cpu, STAT_NEG, (temp & NEGATIVE_BIT));
		// checking for underflow: it has occurred if the result is the opposite sign of the operands
		// AND the operands are of same sign 
		bool operands_same_sign = !((cpu->acc ^ val) & NEGATIVE_BIT);
		bool result_and_acc_opposite_sign = (cpu->acc ^ temp) & NEGATIVE_BIT;
		// set overflow bit
		cpu_set_status_bit(cpu, STAT_OVERFLOW, operands_same_sign && result_and_acc_opposite_sign);
	}
	// set accumulator value
	cpu->acc = (temp & LOW_BYTE_MASK);
}

/* Logical AND */
void op_and(Cpu * cpu, uint16_t arg){
	
}

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
